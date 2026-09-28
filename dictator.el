(require 'subr-x)

(defvar dictator-mode-syntax-table
  (let ((table (make-syntax-table)))
	(modify-syntax-entry ?' "\"" table)
    (modify-syntax-entry ?# "<" table)
    (modify-syntax-entry ?\n ">" table)
    table))

(defun dictator-keywords () '("rule" "when" "var" "->" "_"))

(defun dictator-font-lock-keywords ()
  (list
   ;`("# *\\(warn\\|error\\)" . font-lock-warning-face)
   ;`("# *[#a-zA-Z0-9_]+" . font-lock-preprocessor-face)
   ;`("# *include\\(?:_next\\)?\\s-+\\(\\(<\\|\"\\).*\\(>\\|\"\\)\\)" . (1 font-lock-string-face))
   ;`("\\(?:enum\\|struct\\)\\s-+\\([a-zA-Z0-9_]+\\)" . (1 font-lock-type-face))
   ;`(,(regexp-opt (simpc-keywords) 'symbols) . font-lock-keyword-face)
   `(,(regexp-opt (dictator-keywords) 'symbols) . font-lock-keyword-face)))

(define-derived-mode dictator-mode prog-mode "dictator"
  "simple major mode for editing dictator files"
  :syntax-table dictator-mode-syntax-table
  (setq-local font-lock-defaults '(dictator-font-lock-keywords))
  (setq-local comment-start "# ")
  )

(provide 'dictator-mode)
