#ifndef INDEX_DATABASE_UPDATE_COLLECTOR_H
#define INDEX_DATABASE_UPDATE_COLLECTOR_H
class CTransaction;
struct TransactionLocationReference;
class CCoinsViewCache;
struct IndexDatabaseUpdates;

class IndexDatabaseUpdateCollector
{
private:
    IndexDatabaseUpdateCollector(){};
public:
    static void RecordTransaction(
        const CTransaction& tx,
        const TransactionLocationReference& txLocationRef,
        const CCoinsViewCache& view,
        IndexDatabaseUpdates& indexDatabaseUpdates);
};
#endif// INDEX_DATABASE_UPDATE_COLLECTOR_H