#!/usr/bin/env bash

instrumenterPath=$1

sed -i "s;PIRA_SUBMODULE_PATH;\"$instrumenterPath\";g" ./src/tools/instrumenter/scorep_instrumenter_compiler.cpp
