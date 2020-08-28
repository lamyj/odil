#!/bin/bash

CI_TYPE=${CI_TYPE:?}
WORKSPACE=${WORKSPACE:?}

if [ "${RUNNER}" = "docker" ]; then
  IMAGE=${IMAGE:?}
  CONTAINER=${IMAGE//:/_}
  PRE_START="docker run -di -v ${WORKSPACE}:${WORKSPACE} --name ${CONTAINER:?} --rm ${IMAGE}"
  RUNNER="docker exec -w ${WORKSPACE} -e WORKSPACE=${WORKSPACE} ${CONTAINER:?}"
  POST_END="docker kill ${CONTAINER:?}"
else
  PRE_START=""
  RUNNER=""
  POST_END=""
fi

${PRE_START}

${RUNNER} ./.ci/${CI_TYPE}/install \
  && ${RUNNER} ./.ci/${CI_TYPE}/build \
  && ${RUNNER} ./.ci/${CI_TYPE}/post_build

${POST_END}
