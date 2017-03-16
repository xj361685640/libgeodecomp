@echo off
rem Windows wrapper for the original Python script as Windows doesn't
rem know what a shebang is.

IF "%PYTHON%" == "" GOTO DEFAULT_PYTHON
:PYTHON_OVERRIDE
"%PYTHON%" %0 --python "%PYTHON%" %*
GOTO END
:DEFAULT_PYTHON
python %0 %*
GOTO END
:END

exit /B 0

