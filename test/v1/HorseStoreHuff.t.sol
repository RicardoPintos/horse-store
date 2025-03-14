// SPDX-License-Identifier: GPL-3.0-only
pragma solidity 0.8.20;

import {BaseTestV1, IHorseStore} from "./BaseTestV1.t.sol";
import {HuffDeployer} from "foundry-huff/HuffDeployer.sol";

contract HorseStoreHuffTest is BaseTestV1 {
    string public constant HORSE_STORE_HUFF_LOCATION =
        "horseStoreV1/HorseStore";

    function setUp() public override {
        horseStore = IHorseStore(
            HuffDeployer.config().deploy(HORSE_STORE_HUFF_LOCATION)
        );
    }
}
