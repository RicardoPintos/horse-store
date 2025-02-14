// 1. CONTRACT CREATION CODE //
// Free memory pointer //
PUSH1 0x80          // [0x80]
PUSH1 0x40          // [0x40, 0x80]
MSTORE              // []       // MEMORY [0x40 ~~> 0x80]
// If someone sends any ether to the contract, revert //
CALLVALUE           // [msg.value]
DUP1                // [msg.value, msg.value]
ISZERO              // [msg.valu == 0, msg.value]
PUSH1 0x0e          // [0x0e, msg.value == 0, msg.value]
JUMPI               // [msg.value]       // JUMP over the revert code if msg.value == 0
PUSH0               // [0x00, msg.value]
DUP1                // [0x00, 0x00, msg.value]
REVERT              // [msg.value]
// [0x0e program counter]
JUMPDEST            // [msg.value]
POP                 // []
PUSH1 0xa5          // [0xa5]
DUP1                // [0xa5, 0xa5]
PUSH2 0x001b        // [0x001b, 0xa5, 0xa5]
PUSH0               // [0x00, 0x001b, 0xa5, 0xa5]
CODECOPY            // [0xa5]     // MEMORY [runtime code]
PUSH0               // [0x00, 0xa5]  // MEMORY [runtime code]
RETURN              // []         // MEMORY [runtime code]
INVALID             // [end]      // MEMORY [runtime code]

// 2. RUNTIME CODE //
// Entry point of all calls //
// Free memory pointer //
PUSH1 0x80          // [0x80]
PUSH1 0x40          // [0x40, 0x80]
MSTORE              // []       // MEMORY [0x40 ~~> 0x80]
// If someone sends any ether to the contract, revert //
CALLVALUE           // [msg.value]
DUP1                // [msg.value, msg.value]
ISZERO              // [msg.valu == 0, msg.value]
PUSH1 0x0e          // [0x0e, msg.value == 0, msg.value]
JUMPI               // [msg.value]       // JUMP over the revert code if msg.value == 0
PUSH0               // [0x00, msg.value]
DUP1                // [0x00, 0x00, msg.value]
REVERT              // [msg.value]
// [0x0e program counter]
JUMPDEST            // [msg.value]
POP                 // []
PUSH1 0x04          // [0x04]
CALLDATASIZE        // [calldata size]
LT                  // [calldata size < 0x04]
PUSH1 0x30          // [0x30, calldata size < 0x04]
JUMPI               // []
// If the calldata size is less than 4 bytes (the function selector), revert //
PUSH0               // [0x00]
CALLDATALOAD        // [32 bytes of calldata]
PUSH1 0xe0          // [0xe0, 32 bytes of calldata]
SHR                 // [calldata[0:4]]  // function selector
DUP1                // [func_selector, func_selector]
// set_number_of_horses DISPATCH //
PUSH4 0xcdfead2e    // [0xcdfead2e, func_selector, func_selector]
EQ                  // [0xcdfead2e == func_selector, func_selector]
PUSH1 0x34          // [0x34, 0xcdfead2e == func_selector, calldata[0:4]]
JUMPI               // [func_selector] // if true, jump to set_number_of_horses
DUP1                // [func_selector, func_selector]
// get_number_of_horses DISPATCH //
PUSH4 0xe026c017    // [0xe026c017, func_selector, func_selector]
EQ                  // [0xe026c017 == func_selector, func_selector]
PUSH1 0x45          // [0x45, 0xe026c017 == func_selector, func_selector]
JUMPI               // [func_selector] // if true, jump to get_number_of_horses
// [0x30 program counter] Revert Jump Destination //
JUMPDEST            // []
PUSH0               // [0x00]
DUP1                // [0x00, 0x00]
REVERT              // [revert call]
// [updateHorseNumber JUMPI]
JUMPDEST            // [func_selector]
PUSH1 0x43          // [0x43, func_selector]
PUSH1 0x3f          // [0x3f, 0x43, func_selector]
CALLDATASIZE        // [calldata size, 0x3f, 0x43, func_selector]
PUSH1 0x04          // [0x04, calldata size, 0x3f, 0x43, func_selector]
PUSH1 0x59          // [0x59, 0x04, calldata size, 0x3f, 0x43, func_selector]
JUMP                // [Raw Jump to 0x59]
// Jump Destination to store value //
JUMPDEST            // [calldata_value_to_update, 0x43, func_selector]
PUSH0               // [0x00, calldata_value_to_update, 0x43, func_selector]
SSTORE              // [store_value_in_zero_storage_slot, 0x43, func_selector]
JUMP                // [Jump to 0x43 with func_selector]
JUMPDEST            // [func_selector]
STOP                // [end_execution]
// Jump Destination to get value //
JUMPDEST            // [func_selector]
PUSH0               // [0x00, func_selector]
SLOAD               // [numHorses, func_selector]
PUSH1 0x40          // [0x40, numHorses, func_selector]
MLOAD               // [0x80, numHorses, func_selector]  // Memory [0x40 ~~> 0x80]
SWAP1               // [numHorses, 0x80, func_selector]
DUP2                // [0x80, numHorses, 0x80, func_selector]
MSTORE              // [0x80, func_selector]    // Memory [0x80 ~~> numHorses]
PUSH1 0x20          // [0x20, 0x80, func_selector]
ADD                 // [0xa0, func_selector]
PUSH1 0x40          // [0x40, 0xa0, func_selector]
MLOAD               // [0x80, 0xa0, func_selector]      // Memory [0x40 ~~> 0xa0][0x80 ~~> numHorses]
DUP1                // [0x80, 0x80, 0xa0, func_selector]
SWAP2               // [0xa0, 0x80, 0x80, func_selector]
SUB                 // [0x20, 0x80, func_selector]
SWAP1               // [0x80, 0x20, func_selector]
RETURN              // [position:0x80, value:numHorses, size:32bytes(0x20), func_selector]

// [updateHorseNumber JUMPDEST]
// Check to see if there is a value to update
JUMPDEST            // [0x04, calldata size, 0x3f, 0x43, func_selector]
PUSH0               // [0x00, 0x04, calldata size, 0x3f, 0x43, func_selector]
PUSH1 0x20          // [0x20, 0x00, 0x04, calldata size, 0x3f, 0x43, func_selector]
DUP3                // [0x04, 0x20, 0x00, 0x04, calldata size, 0x3f, 0x43, func_selector]
DUP5                // [calldata_size, 0x04, 0x20, 0x00, 0x04, calldata size, 0x3f, 0x43, func_selector]
SUB                 // [calldata_size - 0x04, 0x20, 0x00, 0x04, calldata size, 0x3f, 0x43, func_selector]
SLT                 // [calldata_size - 0x04 < 0x20, 0x00, 0x04, calldata size, 0x3f, 0x43, func_selector]
ISZERO              // [is_calldata_plus_32_bytes, 0x00, 0x04, calldata size, 0x3f, 0x43, func_selector]
PUSH1 0x68          // [0x68, is_calldata_plus_32_bytes, 0x00, 0x04, calldata size, 0x3f, 0x43, func_selector]
JUMPI               // [JUMP to 0x68 if calldata is more than 32 bytes]
// if calldata is less than 32 bytes, revert
PUSH0               // [0x00, ...]
DUP1                // [0x00, 0x00, ...]
REVERT              // [revert call]
// [0x68 program counter] if calldata is more than 32 bytes
JUMPDEST            // [0x00, 0x04, calldata size, 0x3f, 0x43, func_selector]
POP                 // [0x04, calldata size, 0x3f, 0x43, func_selector]
CALLDATALOAD        // [calldata value_to_update, calldata size, 0x3f, 0x43, func_selector]
SWAP2               // [0x3f, calldata_size, calldata_value_to_update, 0x43, func_selector]
SWAP1               // [calldata_size, 0x3f, calldata_value_to_update, 0x43, func_selector]
POP                 // [0x3f, calldata_value_to_update, 0x43, func_selector]
JUMP                // [JUMP to 0x3f]
INVALID
// Metadata //
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
MLOAD
PUSH22 0xaaf855aa11cb07e2f92af07a31c0b0b87009a9a56a8d
SWAP8
INVALID
EXTCODESIZE
DUP15
CODECOPY
INVALID
CALLDATALOAD
EXTCODECOPY
PUSH5 0x736f6c6343
STOP
ADDMOD
EQ
STOP
CALLER