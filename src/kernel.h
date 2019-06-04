// Copyright (c) 2012-2013 The PPCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef BITCOIN_KERNEL_H
#define BITCOIN_KERNEL_H
#include "uint256.h"
#include "streams.h"
#include "arith_uint256.h"
#include "coins.h"

class CBlock;
class CWallet;
class COutPoint;
class CBlockIndex;
class CTransaction;
struct CStakeCache{
    CStakeCache(uint32_t blockFromTime_, uint256 blockFromHash_, CAmount amount_) : blockFromTime(blockFromTime_), blockFromHash(blockFromHash_), amount(amount_){
    }
    uint32_t blockFromTime;
    uint256 blockFromHash;
    CAmount amount;
};

void CacheKernel(std::map<COutPoint, CStakeCache>& cache, const COutPoint& prevout, CBlockIndex* pindexPrev, CCoinsViewCache& view);

// MODIFIER_INTERVAL: time to elapse before new modifier is computed
static const unsigned int MODIFIER_INTERVAL = 60;
static const unsigned int MODIFIER_INTERVAL_TESTNET = 20;
extern unsigned int nModifierInterval;
extern unsigned int getIntervalVersion(bool fTestNet);
// MODIFIER_INTERVAL_RATIO:
// ratio of group interval length between the last group and the first group
static const int MODIFIER_INTERVAL_RATIO = 3;
// To decrease granularity of timestamp
// Supposed to be 2^n-1
static const uint32_t STAKE_TIMESTAMP_MASK = 15;
// Compute the hash modifier for proof-of-stake
bool ComputeNextStakeModifier(const CBlockIndex* pindexPrev, uint64_t& nStakeModifier, bool& fGeneratedStakeModifier);
// Check whether stake kernel meets hash target
// Sets hashProofOfStake on success return
bool CheckStakeKernelHash(unsigned int nBits, unsigned int blockFromTime, uint256 blockFromHash, unsigned int nTxPrevOffset, CAmount nValueIn, const COutPoint& prevout, unsigned int nTimeTx, uint256& hashProofOfStake);
bool CheckStakeKernelHash(unsigned int nBits, const CBlock& blockFrom, unsigned int nTxPrevOffset, const CTransactionRef& txPrev, const COutPoint& prevout, unsigned int nTimeTx, uint256& hashProofOfStake);
// Check kernel hash target and coinstake signature
// Sets hashProofOfStake on success return
bool CheckProofOfStake(const CBlock &block, uint256& hashProofOfStake);
// Check whether the coinstake timestamp meets protocol
bool CheckCoinStakeTimestamp(uint32_t nTimeBlock);
// Get stake modifier checksum
unsigned int GetStakeModifierChecksum(const CBlockIndex* pindex);
// Check stake modifier hard checkpoints
bool CheckStakeModifierCheckpoints(int nHeight, unsigned int nStakeModifierChecksum);
bool CheckKernel(CBlockIndex* pindexPrev, unsigned int nBits, uint32_t nTimeBlock, const COutPoint& prevout, CCoinsViewCache& view, const std::map<COutPoint, CStakeCache>& cache);
bool CheckKernel(CBlockIndex* pindexPrev, unsigned int nBits, uint32_t nTimeBlock, const COutPoint& prevout, CCoinsViewCache& view);
#endif // BITCOIN_KERNEL_H