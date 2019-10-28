#!/bin/bash

GIT_ORIGIN="origin"

CMAKE_PROJECT_DIR="/Users/oleksandr/Work/virgil-iot-sdk"
CMAKE_OUTPUT_DIR="${CMAKE_PROJECT_DIR}/debug"
CMAKE_TARGET="documentation"

DOC_PAGES_DIR="${CMAKE_PROJECT_DIR}/docs/doxygen/html"
GH_PAGES_DIR="/Users/oleksandr/Work/virgil-iot-sdk.gh-pages"


CUR_DIRECTORY=`pwd`

echo ---------------  Prepage output directory  -------------

cd ${GH_PAGES_DIR}
git rm -rf *

echo ----------------  Generate documentation  --------------

cd ${CMAKE_PROJECT_DIR}
CUR_HASH=`git rev-parse HEAD`
CUR_COMMENT=`git log -1 --pretty=%B`
cmake --build ${CMAKE_OUTPUT_DIR} --target ${CMAKE_TARGET}
cp -R -f ${DOC_PAGES_DIR}/ ${GH_PAGES_DIR}

echo ------------  Commit documentation changes  ------------

cd ${GH_PAGES_DIR}
git add *
git commit -m "Documentation changes for commit '${CUR_COMMENT}' ${CUR_HASH}"
git push ${GIT_ORIGIN} gh-pages

cd ${CUR_DIRECTORY}
