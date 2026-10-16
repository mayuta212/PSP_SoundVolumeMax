# Publishing checklist

- Push **contents** of the root folder to a new repository; `.github/workflows/source-tests.yml` is included.
- The workflow runs three Python **source** checks; it is not a toolchain compilation or hardware validation.
- Suggested tag: `minimal-alpha1`; classify as **alpha/pre-release**, not a universal release.
- The source archive intentionally contains **no PRX binary**.
- To attach a binary later, checksum and verify that exact build; see `VALIDATION.md`. Never claim that an unverified CI-generated PRX is the device-tested binary.
- Do not add original Audio Boost PRXs, patches or Sony firmware content.
