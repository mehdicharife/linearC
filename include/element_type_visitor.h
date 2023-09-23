#ifndef ELEMENT_TYPE_VISITOR_H
#define ELEMENT_TYPE_VISITOR_H


typedef struct element_type element_type;

typedef struct element_type_visitor element_type_visitor;

struct element_type_visitor {
    void (*visit_int)(element_type_visitor* pthis, element_type* ptype);
    void (*visit_double)(element_type_visitor* pthis, element_type* ptype);
    void(*visit_string)(element_type_visitor* pthis, element_type* ptype);
};

#endif