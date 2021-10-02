#!/bin/bash -e

# Check sed stuff, basically to support OSX
if [[ $(uname) == 'Linux' ]]
 then
    SED=sed
else
    which gsed > /dev/null
    if [ $? -ne 0 ]; then
        echo 'Install core utils to run this on OSX: brew install coreutils'
        exit 1
    fi

    SED=gsed
fi

##save directory
pushd .

## delete just in case it exists
rm -rf flutter_temp

## download lib/src from Flutter github
echo '### Downloading Flutter source files ###'

git init flutter_temp
cd flutter_temp
git remote add origin git@github.com:flutter/flutter.git
git config core.sparseCheckout true 
echo "packages/flutter/lib/src/" >> .git/info/sparse-checkout 
git pull origin master 

popd

# extract class names and lines into json body

echo '### Building urls ###'


folder=./flutter_temp/packages/flutter/lib/src

grep -E -R -n "^(abstract)* *class [A-Z]" $folder |
$SED -E 's|(abstract)* *class\s(\S*)\s.*|\2|g; s|^./flutter_temp/packages/flutter/lib/src/([^:]*):([^:]*):([^:]*)$|    "\3": "\1#L\2",|gm;  s|(<[A-Z]+?>)||g' |
sort |
head -c -2 > urls.json

# insert json body into template

sed -E "s/CLASS_TEMPLATES/$(sed -e 's/[\&/]/\\&/g' -e 's/$/\\n/' urls.json | tr -d '\n')/" < urlmatcher_template.js > extension/urlmatcher.js

# cleaning up
echo '### cleaning up ###'

rm -rf flutter_temp
rm urls.json
