#!/bin/bash
# ASHEN 远行者 — 一键同步到 GitHub
# 用法：在项目目录下运行 bash git-sync.sh "本次改了什么"

cd "$(dirname "$0")"

MSG="${1:-更新文档 $(date +%Y-%m-%d_%H:%M)}"

echo "=== 检查变更 ==="
git add -A
CHANGED=$(git status --porcelain | wc -l)

if [ "$CHANGED" -eq 0 ]; then
  echo "没有变更，无需同步。"
  exit 0
fi

git status --short

echo ""
echo "=== 提交：$MSG ==="
git commit -m "$MSG"

echo "=== 推送到 GitHub ==="
git push

echo ""
echo "✅ 同步完成！"
echo "仓库：https://github.com/GreatCQ/ASHEN-Wayfarer"
