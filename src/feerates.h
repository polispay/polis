// Copyright (c) 2019 The Polis Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <validation.h>

//! For exclusive use of the header event
extern volatile bool fPoSTrigger;

CFeeRate FallbackFee();
CFeeRate MinTxFee();
CFeeRate MinRelayFee();
