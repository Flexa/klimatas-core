// Copyright (c) 2017-2018 The KTSX developers
// Copyright (c) 2019-2020 The Klimatas developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTS_ZKTSWALLET_H
#define KTS_ZKTSWALLET_H

#include <map>
#include "libzerocoin/Coin.h"
#include "mintpool.h"
#include "uint256.h"
#include "zerocoin.h"

class CDeterministicMint;

class CzKTSWallet
{
private:
    uint256 seedMaster;
    uint32_t nCountLastUsed;
    std::string strWalletFile;
    CMintPool mintPool;

public:
    CzKTSWallet(std::string strWalletFile);

    void AddToMintPool(const std::pair<uint256, uint32_t>& pMint, bool fVerbose);
    bool SetMasterSeed(const uint256& seedMaster, bool fResetCount = false);
    uint256 GetMasterSeed() { return seedMaster; }
    void SyncWithChain(bool fGenerateMintPool = true);
    void GenerateDeterministicZKTS(libzerocoin::CoinDenomination denom, libzerocoin::PrivateCoin& coin, CDeterministicMint& dMint, bool fGenerateOnly = false);
    void GenerateMint(const uint32_t& nCount, const libzerocoin::CoinDenomination denom, libzerocoin::PrivateCoin& coin, CDeterministicMint& dMint);
    void GetState(int& nCount, int& nLastGenerated);
    bool RegenerateMint(const CDeterministicMint& dMint, CZerocoinMint& mint);
    void GenerateMintPool(uint32_t nCountStart = 0, uint32_t nCountEnd = 0);
    bool LoadMintPoolFromDB();
    void RemoveMintsFromPool(const std::vector<uint256>& vPubcoinHashes);
    bool SetMintSeen(const CBigNum& bnValue, const int& nHeight, const uint256& txid, const libzerocoin::CoinDenomination& denom);
    bool IsInMintPool(const CBigNum& bnValue) { return mintPool.Has(bnValue); }
    void UpdateCount();
    void Lock();
    void SeedToZKTS(const uint512& seed, CBigNum& bnValue, CBigNum& bnSerial, CBigNum& bnRandomness, CKey& key);
    bool CheckSeed(const CDeterministicMint& dMint);

private:
    uint512 GetZerocoinSeed(uint32_t n);
};

#endif //KTS_ZKTSWALLET_H
