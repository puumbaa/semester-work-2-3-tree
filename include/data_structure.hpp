//
// Created by user on 20.04.2021.
//
#pragma once
#ifndef SEMESTER_WORK_TEMPLATE_DATA_STRUCTURE_HPP
#define SEMESTER_WORK_TEMPLATE_DATA_STRUCTURE_HPP

#endif  //SEMESTER_WORK_TEMPLATE_DATA_STRUCTURE_HPP
#include "node.hpp"
namespace itis {
  struct TwoThreeTree{

    void Clear();

    void Insert(int k);

    TwoThreeNode *Search(int k);

    TwoThreeNode *Remove(int k);

    TwoThreeNode *root();

    int Height();

    ~TwoThreeTree();




  };
}

