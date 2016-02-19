#!/usr/bin/env bash

echo "upload..."
#scp -r `ls | grep -v 'bin' | grep -v 'upload.sh'` spm1510@r720-phi.itc.unipi.it:SPM-project

rsync -avz --exclude-from '.rsyncignore' -e ssh . spm1505@r720-phi.itc.unipi.it:SPM-project
rsync -av -e ssh spm1505@r720-phi.itc.unipi.it:SPM-project/testResults .
echo "done!"