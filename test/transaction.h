#ifndef TRANSACTION_H
#define TRANSACTION_H
#include "model.h"

class Transaction : public Model
{
public:
    ELOQUENT_MODEL(Transaction, transactions, id)
};
#endif // TRANSACTION_H
