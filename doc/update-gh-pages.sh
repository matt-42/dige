#! /bin/sh

mkdir -p gh-pages/
cd gh-pages
if  [ ! -d  dige/.git ]; then
    git clone git@github.com:matt-42/dige.git -b gh-pages
fi
cd dige

cp ../../index.html .
git commit -a -m "Update gh-pages"
git push git@github.com:matt-42/dige.git gh-pages
