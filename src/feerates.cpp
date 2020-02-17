// Copyright (c) 2019 The Polis Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <validation.h>

//! For exclusive use of the header event
volatile bool fPoSTrigger = false;

static const CAmount DEFAULT_FALLBACK_LEGACY = 50 * COIN;
static const CAmount DEFAULT_FALLBACK_FUTURE = 0.5 * COIN;

CFeeRate FallbackFee() {
	if(fPoSTrigger||IsPoS())
		return CFeeRate(DEFAULT_FALLBACK_FUTURE);
	return CFeeRate(DEFAULT_FALLBACK_LEGACY);
}

static const CAmount DEFAULT_TX_MINFEE_LEGACY = 50 * COIN;
static const CAmount DEFAULT_TX_MINFEE_FUTURE = 0.5 * COIN;

CFeeRate MinTxFee() {
	if(fPoSTrigger||IsPoS())
		return CFeeRate(DEFAULT_TX_MINFEE_FUTURE);
	return CFeeRate(DEFAULT_TX_MINFEE_LEGACY);
}

static const CAmount DEFAULT_MIN_RELAY_FEE_LEGACY = 50 * COIN;
static const CAmount DEFAULT_MIN_RELAY_FEE_FUTURE = 0.5 * COIN;

CFeeRate MinRelayFee() {
	if(fPoSTrigger||IsPoS())
		return CFeeRate(DEFAULT_MIN_RELAY_FEE_FUTURE);
	return CFeeRate(DEFAULT_MIN_RELAY_FEE_LEGACY);
}
