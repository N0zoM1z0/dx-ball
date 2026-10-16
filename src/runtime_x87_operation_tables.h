#ifndef DXBALL_RUNTIME_X87_OPERATION_TABLES_H
#define DXBALL_RUNTIME_X87_OPERATION_TABLES_H

/* Machine entry addresses only. Their x87/register ABI is not callable as C. */
typedef struct DxBallX87EntryAddress DxBallX87EntryAddress;
typedef struct DxBallX87OperationHeader {
    unsigned char name_length;
    char name[11];
    unsigned char unclassified_0c;
    unsigned char operand_count;
    unsigned short operation;
} DxBallX87OperationHeader;
typedef struct DxBallX87UnaryOperation {
    DxBallX87OperationHeader header;
    const DxBallX87EntryAddress *dispatch[4];
} DxBallX87UnaryOperation;
typedef struct DxBallX87BinaryOperation {
    DxBallX87OperationHeader header;
    const DxBallX87EntryAddress *dispatch[16];
} DxBallX87BinaryOperation;

extern DxBallX87UnaryOperation dxball_x87_asin_operation;
extern DxBallX87UnaryOperation dxball_x87_acos_operation;
extern DxBallX87UnaryOperation dxball_x87_atan_operation;
extern DxBallX87BinaryOperation dxball_x87_atan2_operation;

#endif
