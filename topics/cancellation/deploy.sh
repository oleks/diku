#!/usr/bin/env bash

set -euo pipefail

# Use -B to keep gh-pages at most one commit ahead of master.
# This leads to the use of -f when pushing to gh-pages on remote.
# This might actually be one descent use of git push -f..
git checkout -B gh-pages

set +e
cat | bash - <<EOF
set -euo pipefail

FILES=index.html

rm -f \${FILES}
rm -rf ltxpng/
emacs index.org --batch -f org-html-export-to-html --kill
git add -f \${FILES}
git add -f ltxpng/*
git commit -S -m 'Deploy'
git push -f origin gh-pages
EOF
set -e

git checkout master
