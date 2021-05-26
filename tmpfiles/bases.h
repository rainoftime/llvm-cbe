/*
 * base.h
 *
 *  Created on: 2021年5月26日
 *      Author: prism
 */

#ifndef LIB_TARGET_CBACKEND_BASES_H_
#define LIB_TARGET_CBACKEND_BASES_H_


#include "llvm/IR/Value.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "utils.h"

#include <random>
#include <initializer_list>


class PuzzleBuilder {
public:
    const static std::string id;

    PuzzleBuilder() {
      puzzle_code = 0;
      module = nullptr;
    }

    PuzzleBuilder(uint64_t puzzle_code, llvm::Module *M) :
            puzzle_code(puzzle_code), module(M) {}

    virtual llvm::Value *build(SymvarLoc &svs_locs, llvm::Instruction *insert_point) = 0;

    virtual std::unique_ptr<PuzzleBuilder> clone(uint64_t, llvm::Module*) = 0;

protected:
    llvm::Module *module;
    uint64_t puzzle_code;
};


template <typename T> class Transformer {
public:
    const static std::string id;

    Transformer() {
      trans_code = 0;
    }

    explicit Transformer(uint64_t trans_code) : trans_code(trans_code) {}

    virtual T *transform(T *t, llvm::Value *predicate) = 0;

    virtual std::unique_ptr<Transformer<T>> clone(uint64_t) = 0;

protected:
    uint64_t trans_code;
};


#endif /* LIB_TARGET_CBACKEND_BASES_H_ */
