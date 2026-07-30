# GENGFaker Team Note

서울대학교 팀 GENGFaker의 2026년 UCPC용 알고리즘 팀노트입니다. KACTL 형식의
LaTeX 문서와 C++ 알고리즘 스니펫으로 구성되어 있습니다.

[완성된 팀노트 PDF](teamnote.pdf)

## 구성

- `content/teamnote.tex`: 문서 진입점과 팀 정보
- `content/*/chapter.tex`: 분야별 목차와 설명
- `content/**/*.h`: C++ 알고리즘 스니펫
- `content/tex/`: KACTL 스타일과 전처리 도구
- `teamnote.pdf`: 빌드된 최신 PDF

현재 자료 구조, 조합론, 수학, DP 최적화, 그래프, 기하, 문자열 알고리즘을
포함합니다.

## 빌드

TeX Live, Python 3, GNU Make가 필요합니다. LaTeX 패키지로 `extreport`,
`kotex`, `physics`, `float` 등을 사용합니다.

```bash
make
```

목차까지 안정적으로 갱신하기 위해 기본 빌드는 LaTeX를 두 번 실행합니다.
빠르게 한 번만 빌드하려면 `make fast`, import 경로 검사까지 함께 실행하려면
`make check`를 사용합니다.

```bash
make fast
make check
make clean
```

빌드 중 KACTL 전처리기를 실행하므로 `pdflatex`의 `-shell-escape` 옵션이
사용됩니다.

## 스니펫 추가

1. 해당 분야의 `content/<category>/` 아래에 헤더를 추가합니다.
2. 같은 폴더의 `chapter.tex`에 `\kactlimport{FileName.h}`를 추가합니다.
3. Linux에서도 동작하도록 import의 대소문자를 실제 파일명과 정확히 맞춥니다.
4. `make check`로 import와 PDF 빌드를 검증합니다.

각 헤더는 팀노트에 삽입되는 스니펫이며, 일부는 필요한 타입 별칭이나 표준
라이브러리 include를 문서 외부에서 제공한다고 가정합니다.

## 출처와 라이선스

일부 파일은 헤더 주석에 저자, 원 출처, 개별 라이선스가 기재되어 있습니다.
저장소 전체에 적용되는 라이선스는 아직 지정하지 않았습니다. 공개 배포 전에
각 스니펫의 출처와 재배포 조건을 확인하고, 저장소 수준의 `LICENSE`를
추가하는 것을 권장합니다.
