#ifndef BEHAVIORAL_CHAIN_OF_RESPONSIBILITY_CHAIN_OF_RESPONSIBILITY_H_
#define BEHAVIORAL_CHAIN_OF_RESPONSIBILITY_CHAIN_OF_RESPONSIBILITY_H_

class AbstractExemptHandler {
public:
    virtual bool ExemptHandler() = 0;
    void setNext(AbstractExemptHandler*);

private:
    AbstractExemptHandler* m_next;
};

class DepartmentExemptHandler : public AbstractExemptHandler {
public:
    bool ExemptHandler();
};

class InstituteExemptHandler : public AbstractExemptHandler {
public:
    bool ExemptHandler();
};

class CollegeExemptHandler : public AbstractExemptHandler {
public:
    bool ExemptHandler();
};

#endif