# GitHub公開手順（ソースのみ）

1. ZIPを展開し、`SoundVolumeMax_GitHub_alpha1` の**中身**を新しいGitHubリポジトリのルートに置く。README、LICENSE、`.github/workflows/source-tests.yml` を含める。
2. `README_ja.md` と `docs/` の音量・接続注意を確認する。
3. 公開リポジトリにpushすると、GitHub Actionsで**ソースの3テストのみ**実行される。CIでは実機の音量も、正式なPSPDEVビルドも検証しない。
4. Releaseタグは例として `minimal-alpha1`。ソースZIPにはPRXが入っていないので、**バイナリ配布済みと書かない**。
5. ビルド済みのPRXを別途公開するなら、必ず実体のSHA-256を照合する。前回実機成功したビルドのハッシュは `5a322c22bd2658cdd6ed6118cde592e7ea11584c4917e23ae34446b20530f465`。違うハッシュの生成物は未検証と扱う。
6. 元のAudio BoostのPRX、改変パッチ、ファームウェアのダンプを添付しない。

Gitで空のリポジトリへ登録する例：

```bash
cd /mnt/c/Users/hujay/Downloads/SoundVolumeMax_GitHub_alpha1
git init
git add .
git commit -m "Publish Sound Volume Max Minimal alpha1 source"
```

その後、GitHubで空のリポジトリを作り、GitHub側が提示する`git remote add origin ...`と`git push`を実行してください。
