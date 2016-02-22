#!/usr/bin/env bash

#
# upload.sh
#             synchronize the local project with the remote host machine.
#            Download olso the tests from the host machine in the folder testResults/.
#

echo "upload..."

rsync -avz --exclude-from '.rsyncignore' -e ssh . spm1505@r720-phi.itc.unipi.it:SPM-StreamCluster
rsync -av -e ssh spm1505@r720-phi.itc.unipi.it:SPM-StreamCluster/testResults .
echo "done!"