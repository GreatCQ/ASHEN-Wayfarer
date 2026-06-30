@echo off
chcp 65001 >nul 2>&1
REM ASHEN 远行者 — 一键同步到 GitHub
REM 双击运行，或在命令行: git-sync.bat "本次改了什么"

cd /d "%~dp0"

set "MSG=%*"
if "%MSG%"=="" set "MSG=更新文档 %date% %time%"

echo === 检查变更 ===
git add -A

git diff --cached --stat | findstr /R "." >nul
if errorlevel 1 (
  echo 没有变更，无需同步。
  pause
  exit /b 0
)

git status --short

echo.
echo === 提交：%MSG% ===
git commit -m "%MSG%"

echo === 推送到 GitHub ===
git push

echo.
echo ✅ 同步完成！
echo 仓库：https://github.com/GreatCQ/ASHEN-Wayfarer
pause
