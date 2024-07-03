[[유용한 단축키 정리|단축키]]를 정의할때 `"when"`이라는 옵션이 있다. 바로 이 단축키가 언제 동작하게 하느냐인데,
`default settings.json`파일에 보면 vim plugin의 특정 mode에서 동작하는 키를 구현하는 조건문이 나온다.
```json
"when": "editorTextFocus && inputFocus && notebookEditorFocused && vim.mode == 'Normal' && notebookEditorCursorAtBoundary != 'bottom' && notebookEditorCursorAtBoundary != 'none'"
```
대게는 이런식이다. 여기에 보면 `vim.mode == 'Normal'` 옵션이 있다. vim의 normal mode를 가리킨다.
`editorTextFocus` 옵션도 중요하다. editor text에 포커스가 있어야한다는 조건이다.
`vim.active`는 vim plugin이 활성화되어있느냐를 나타내는것 같다.

이걸 이용하면 vim의 insert 모드에서 `ctrl+c`같은 기능을 활성화 시킬 수 있다.
```json
  {
    "key": "ctrl+c",
    "command": "extension.vim_escape",
    "when": "editorTextFocus && vim.active && !inDebugRepl && vim.mode == 'Insert'"
  },
```

특히, default settings에서 보면 `"command": "extension.vim_ctrl+b"` 와 같은 것들이 보인다. 이것은 vim plugin에서 vim의 ctrl 키바인딩 기능을 vscode에서 사용하게 해주는 것으로 보인다.