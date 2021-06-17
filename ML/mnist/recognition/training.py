import torch
import torch.optim as optim


def train_model(model, train_loader, val_loader, config):
    optimizer = getattr(optim, config['optimizer'])(model.parameters(), config['learning_rate'])
    n_epochs = config['n_epochs']
    device = config['device']
    criterion = config['criterion']
    best_acc = 0.0

    for epoch in range(n_epochs):
        train_acc = 0.0
        train_loss = 0.0
        val_acc = 0.0
        val_loss = 0.0

        # training
        model.train()
        for i, data in enumerate(train_loader):
            inputs, labels = data
            inputs, labels = inputs.to(device), labels.to(device)
            optimizer.zero_grad()
            outputs = model(inputs)
            batch_loss = criterion(outputs, labels)
            _, train_pred = outputs.max(1, keepdim=True)
            batch_loss.backward()
            optimizer.step()

            train_acc += train_pred.eq(labels.view_as(train_pred)).sum().item()
            train_loss += batch_loss.item()

        # validation
        model.eval()

        with torch.no_grad():
            for i, data in enumerate(val_loader):
                inputs, labels = data
                inputs, labels = inputs.to(device), labels.to(device)
                outputs = model(inputs)
                batch_loss = criterion(outputs, labels)
                _, val_pred = outputs.max(1, keepdim=True)

                val_acc += val_pred.eq(labels.view_as(val_pred)).sum().item()
                val_loss += batch_loss.item()

            print('[{:03d}/{:03d}] Train Acc: {:3.6f} Loss: {:3.6f} | Val Acc: {:3.6f} loss: {:3.6f}'.format(
                epoch + 1, n_epochs, train_acc / len(train_loader.dataset), train_loss / len(train_loader),
                val_acc / len(val_loader.dataset), val_loss / len(val_loader)
            ))

            if val_acc > best_acc:
                best_acc = val_acc
                torch.save(model.state_dict(), config['model_path'])
                print('saving model with acc {:.3f}'.format(best_acc / len(val_loader.dataset)))
