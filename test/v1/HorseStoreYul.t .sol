// SPDX-License-Identifier: GPL-3.0-only
pragma solidity 0.8.20;

import {BaseTestV1, IHorseStore} from "./BaseTestV1.t.sol";
import {HorseStoreYul} from "../../src/horseStoreV1/HorseStoreYul.sol";

contract HorseStoreYulTest is BaseTestV1 {
    function setUp() public override {
        horseStore = IHorseStore(address(new HorseStoreYul()));
    }
}
