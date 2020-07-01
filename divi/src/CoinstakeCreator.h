#ifndef COINSTAKE_CREATOR_H
#define COINSTAKE_CREATOR_H

#include <stdint.h>
#include <amount.h>
#include <set>
#include <utility>
#include <vector>

class CWallet;
class CBlock;
class CMutableTransaction;
class CKeyStore;
class CWalletTx;

class CoinstakeCreator
{
private:
    CWallet& wallet_;
    int64_t& coinstakeSearchInterval_;

    void CombineUtxos(
        const CAmount& allowedStakingAmount,
        CMutableTransaction& txNew,
        CAmount& nCredit,
        std::set<std::pair<const CWalletTx*, unsigned int> >& setStakeCoins,
        std::vector<const CWalletTx*>& walletTransactions);

    bool SetSuportedStakingScript(
        const std::pair<const CWalletTx*, unsigned int>& transactionAndIndexPair,
        CMutableTransaction& txNew);

    bool SelectCoins(
        CAmount allowedStakingBalance,
        int& nLastStakeSetUpdate,
        std::set<std::pair<const CWalletTx*, unsigned int> >& setStakeCoins);

    bool CreateCoinStake(
        const CKeyStore& keystore, 
        unsigned int nBits, 
        int64_t nSearchInterval, 
        CMutableTransaction& txNew,
        unsigned int& nTxNewTime);
    bool FindStake(
        unsigned int nBits,
        unsigned int& nTxNewTime,
        std::pair<const CWalletTx*, unsigned int>& stakeData,
        CMutableTransaction& txNew);
public:
    CoinstakeCreator(
        CWallet& wallet,
        int64_t& coinstakeSearchInterval);
    bool CreateProofOfStake(
        uint32_t blockBits,
        int64_t nSearchTime, 
        int64_t& nLastCoinStakeSearchTime, 
        CMutableTransaction& txCoinStake,
        unsigned int& nTxNewTime);
};
#endif // COINSTAKE_CREATOR_H