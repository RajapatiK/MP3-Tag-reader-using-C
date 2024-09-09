#ifndef TYPES_H
#define TYPES_H

/* Status will be used in fn. return type */
typedef enum
{
    e_success,
    e_failure
} Status;

typedef enum
{
    v_view,
    e_edit,
    help,
    e_unsupported
} OperationType;

#endif

