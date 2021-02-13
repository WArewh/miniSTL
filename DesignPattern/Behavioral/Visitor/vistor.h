#ifndef BEHAVIORAL_VISITOR_VISITOR_H_
#define BEHAVIORAL_VISITOR_VISITOR_H_

class File;
class Dir;

class AbstractVistor {
public:
    // 对数据访问是易变的

    virtual void visit(const File* file) = 0;
    virtual void visit(const Dir* dir) = 0;
};

class Entry {
public:
    virtual void show(AbstractVistor* vistor) = 0;
};

class File : public Entry {
public:
    void show(AbstractVistor* vistor) { vistor->visit(this); }
};

class Dir : public Entry {};


class ConsoleVistor : public AbstractVistor {
public:
    virtual void visit(const File* file);
    virtual void visit(const Dir* dir);
};

class DesktopVistor : public AbstractVistor {
public:
    virtual void visit(const File* file);
    virtual void visit(const Dir* dir);
};

#endif