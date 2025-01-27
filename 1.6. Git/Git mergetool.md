[이 글](https://gist.github.com/karenyyng/f19ff75c60f18b4b8149/e6ae1d38fb83e05c4378d8e19b014fd8975abb39) 참고
`git config merge.tool nvimdiff`
`git config merge.conflictstyle diff3`
`git mergetool`
```
+--------------------------------+
| LOCAL  |     BASE     | REMOTE |
+--------------------------------+
|             MERGED             |
+--------------------------------+
```
```
:diffg RE  # get from REMOTE
:diffg BA  # get from BASE
:diffg LO  # get from LOCAL
]c - Jump to the next change.
[c - Jump to the previous change.
```