#ifndef NODE_STATE_REGISTRY_H
#define NODE_STATE_REGISTRY_H
#include <NodeId.h>
#include <vector>
#include <string>

class CChain;
struct CNodeState;
class uint256;
class CBlockIndex;
class BlockMap;
class CAddress;
class CAddrMan;

// Requires cs_main.
CNodeState* State(NodeId nodeId);
CAddrMan& GetNetworkAddressManager();
void InitializeNode(NodeId nodeid, const std::string addressName, const CAddress& addr);
void FinalizeNode(NodeId nodeid);
void UpdatePreferredDownload(NodeId nodeId, bool updatedStatus);
bool HavePreferredDownloadPeers();
int SyncStartedNodeCount();
void RecordNodeStartedToSync();
void MarkBlockAsReceived(const uint256& hash);
void MarkBlockAsInFlight(NodeId nodeid, const uint256& hash, CBlockIndex* pindex = nullptr);
bool BlockIsInFlight(const uint256& hash);
NodeId GetSourceOfInFlightBlock(const uint256& hash);
void ProcessBlockAvailability(const BlockMap& blockIndicesByHash, NodeId nodeid);
void UpdateBlockAvailability(const BlockMap& blockIndicesByHash, NodeId nodeid, const uint256& hash);
void FindNextBlocksToDownload(
    const BlockMap& blockIndicesByHash,
    const CChain& activeChain,
    NodeId nodeid,
    unsigned int count,
    std::vector<CBlockIndex*>& vBlocks,
    NodeId& nodeStaller);
// Requires cs_main.
/** Increase a node's misbehavior score. */
void Misbehaving(NodeId nodeId, int howmuch);
#endif// NODE_STATE_REGISTRY_H