@echo off
chcp 65001 >nul 2>&1
REM ASHEN 远行者 — 版本回档工具
REM 用法：git-rollback.bat 会列出历史版本，输入序号回档

cd /d "%~dp0"

echo === 提交历史（最近20条）===
echo.
git log --oneline -20 --no-decorate
echo.
echo ============================================
echo 操作说明：
echo   1. 输入 commit 前面的部分哈希（如 89bcb43）回退到该版本
echo   2. 回退后文件会恢复到该版本的状态
echo   3. 回退会创建一个新的提交，不会丢失历史
echo ============================================
echo.

set /p HASH="输入要回退到的版本哈希（或按 Ctrl+C 取消）: "

if "%HASH%"=="" (
  echo 未输入哈希，取消操作。
  pause
  exit /b 0
)

echo.
echo === 回退到 %HASH% ===
git revert --no-commit HEAD...%HASH%
git commit -m "回档到 %HASH%"

echo === 推送到 GitHub ===
git push

echo.
echo ✅ 回档完成！
echo 如果回档有问题，可以用 git log 查看历史，再回退回来。
pause
