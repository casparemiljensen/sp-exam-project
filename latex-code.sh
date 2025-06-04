#!/usr/bin/env bash

set -e
#set -x

author="$1"
title="$2"
if [ -z "$author" ]; then
	echo -n "Enter the name of the author: "
	read author
fi

if [ -z "$title" ]; then
	echo -n "Enter the title: "
	read title
fi

if command -v pandoc > /dev/null ; then
    PANDOC="$(command -v pandoc)"
fi

function make_latex {
	author=$1
	cat <<'EOF'
\documentclass[a4paper]{article}

\usepackage[a4paper, total={18cm, 26cm}]{geometry}
\usepackage[T1]{fontenc} % needed by beramono
\usepackage{textcomp}
\usepackage{textgreek} % Greek letters
% beramono.sty and MnSymbol.sty come with texlive-fonts-extra in Debian
\usepackage[scaled=0.85]{beramono} % tt font supporting slshape and zero with dot
\usepackage{MnSymbol} % fancy symbols for line-breaks
\usepackage[utf8]{inputenc}
\usepackage{listingsutf8}  % code listings, comes with texlive-latex-recommended
%\usepackage{listings}
\usepackage{xcolor}
\usepackage{verbatim}
\usepackage{graphicx} % \includegraphics[width=\textwidth]{image.png}
\usepackage{pdfpages} % insert PDF, comes with texlive-latex-recommended

% special characters: https://tex.stackexchange.com/a/574950/35131
\lstset{
  inputencoding=utf8,
  extendedchars=true,
  literate={±}{$\pm$}1 {∅}{$\emptyset$}1
      {á}{{\'a}}1  {é}{{\'e}}1  {í}{{\'i}}1 {ó}{{\'o}}1  {ú}{{\'u}}1
      {Á}{{\'A}}1  {É}{{\'E}}1  {Í}{{\'I}}1 {Ó}{{\'O}}1  {Ú}{{\'U}}1
      {à}{{\`a}}1  {è}{{\`e}}1  {ì}{{\`i}}1 {ò}{{\`o}}1  {ù}{{\`u}}1
      {À}{{\`A}}1  {È}{{\`E}}1  {Ì}{{\`I}}1 {Ò}{{\`O}}1  {Ù}{{\`U}}1
      {ä}{{\"a}}1  {ë}{{\"e}}1  {ï}{{\"i}}1 {ö}{{\"o}}1  {ü}{{\"u}}1
      {Ä}{{\"A}}1  {Ë}{{\"E}}1  {Ï}{{\"I}}1 {Ö}{{\"O}}1  {Ü}{{\"U}}1
      {â}{{\^a}}1  {ê}{{\^e}}1  {î}{{\^i}}1 {ô}{{\^o}}1  {û}{{\^u}}1
      {Â}{{\^A}}1  {Ê}{{\^E}}1  {Î}{{\^I}}1 {Ô}{{\^O}}1  {Û}{{\^U}}1
      {œ}{{\oe}}1  {Œ}{{\OE}}1  {æ}{{\ae}}1 {Æ}{{\AE}}1  {ß}{{\ss}}1
      {ẞ}{{\SS}}1  {ç}{{\c{c}}}1 {Ç}{{\c{C}}}1 {ø}{{\o}}1  {Ø}{{\O}}1
      {å}{{\aa}}1  {Å}{{\AA}}1  {ã}{{\~a}}1  {õ}{{\~o}}1 {Ã}{{\~A}}1
      {Õ}{{\~O}}1  {ñ}{{\~n}}1  {Ñ}{{\~N}}1  {¿}{{?`}}1  {¡}{{!`}}1
      {„}{\quotedblbase}1 {“}{\textquotedblleft}1 {–}{$-$}1 {-}{$-$}1
      {°}{{\textdegree}}1 {º}{{\textordmasculine}}1 {ª}{{\textordfeminine}}1
      {€}{{\EUR}}1 {£}{{\pounds}}1  {©}{{\copyright}}1  {®}{{\textregistered}}1
      {«}{{\guillemotleft}}1  {»}{{\guillemotright}}1  {Ð}{{\DH}}1  {ð}{{\dh}}1
      {Ý}{{\'Y}}1    {ý}{{\'y}}1    {Þ}{{\TH}}1    {þ}{{\th}}1    {Ă}{{\u{A}}}1
      {ă}{{\u{a}}}1  {Ą}{{\k{A}}}1  {ą}{{\k{a}}}1  {Ć}{{\'C}}1    {ć}{{\'c}}1
      {Č}{{\v{C}}}1  {č}{{\v{c}}}1  {Ď}{{\v{D}}}1  {ď}{{\v{d}}}1  {Đ}{{\DJ}}1
      {đ}{{\dj}}1    {Ė}{{\.{E}}}1  {ė}{{\.{e}}}1  {Ę}{{\k{E}}}1  {ę}{{\k{e}}}1
      {Ě}{{\v{E}}}1  {ě}{{\v{e}}}1  {Ğ}{{\u{G}}}1  {ğ}{{\u{g}}}1  {Ĩ}{{\~I}}1
      {ĩ}{{\~\i}}1   {Į}{{\k{I}}}1  {į}{{\k{i}}}1  {İ}{{\.{I}}}1  {ı}{{\i}}1
      {Ĺ}{{\'L}}1    {ĺ}{{\'l}}1    {Ľ}{{\v{L}}}1  {ľ}{{\v{l}}}1  {Ł}{{\L{}}}1
      {ł}{{\l{}}}1   {Ń}{{\'N}}1    {ń}{{\'n}}1    {Ň}{{\v{N}}}1  {ň}{{\v{n}}}1
      {Ő}{{\H{O}}}1  {ő}{{\H{o}}}1  {Ŕ}{{\'{R}}}1  {ŕ}{{\'{r}}}1  {Ř}{{\v{R}}}1
      {ř}{{\v{r}}}1  {Ś}{{\'S}}1    {ś}{{\'s}}1    {Ş}{{\c{S}}}1  {ş}{{\c{s}}}1
      {Š}{{\v{S}}}1  {š}{{\v{s}}}1  {Ť}{{\v{T}}}1  {ť}{{\v{t}}}1  {Ũ}{{\~U}}1
      {ũ}{{\~u}}1    {Ū}{{\={U}}}1  {ū}{{\={u}}}1  {Ů}{{\r{U}}}1  {ů}{{\r{u}}}1
      {Ű}{{\H{U}}}1  {ű}{{\H{u}}}1  {Ų}{{\k{U}}}1  {ų}{{\k{u}}}1  {Ź}{{\'Z}}1
      {ź}{{\'z}}1    {Ż}{{\.Z}}1    {ż}{{\.z}}1    {Ž}{{\v{Z}}}1  {ž}{{\v{z}}}1
      {α}{{\textalpha}}1   {Α}{{\textAlpha}}1
      {β}{{\textbeta}}1    {Β}{{\textBeta}}1
      {γ}{{\textgamma}}1   {Γ}{{\textGamma}}1
      {δ}{{\textdelta}}1   {Δ}{{\textDelta}}1
      {ε}{{\textepsilon}}1 {Ε}{{\textEpsilon}}1
      {ζ}{{\textzeta}}1    {Ζ}{{\textZeta}}1
      {η}{{\texteta}}1     {Η}{{\textEta}}1
      {θ}{{\texttheta}}1   {Θ}{{\textTheta}}1
      {ι}{{\textiota}}1    {Ι}{{\textIota}}1
      {κ}{{\textkappa}}1   {Κ}{{\textKappa}}1
      {λ}{{\textlambda}}1  {Λ}{{\textLambda}}1
      {μ}{{\textmugreek}}1 {Μ}{{\textMu}}1
      {ν}{{\textnu}}1      {Ν}{{\textNu}}1
      {ξ}{{\textxi}}1      {Ξ}{{\textXi}}1
      {ο}{{\textomikron}}1 {Ο}{{\textOmikron}}1
      {π}{{\textpi}}1      {Π}{{\textPi}}1
      {ρ}{{\textrho}}1     {Ρ}{{\textRho}}1
      {σ}{{\textsigma}}1   {Σ}{{\textSigma}}1   {ς}{{\textvarsigma}}1
      {τ}{{\texttau}}1     {Τ}{{\textTau}}1
      {υ}{{\textupsilon}}1 {Υ}{{\textUpsilon}}1
      {φ}{{\textphi}}1     {Φ}{{\textPhi}}1
      {χ}{{\textchi}}1     {Χ}{{\textChi}}1
      {ψ}{{\textpsi}}1     {Ψ}{{\textPsi}}1
      {ω}{{\textomega}}1   {Ω}{{\textOmega}}1
}

\lstdefinestyle{bwC++}{
  language=C++,
  morekeywords={concept,consteval,constinit,constexpr,co_await,co_return,co_yield,final,noexcept,override,requires,static_assert,thread_local,BENCHMARK,TEST_CASE,SUBCASE,SECTION,CHECK,CHECK_FALSE,CHECK_THROWS_AS,CHECK_THROWS_AS_MESSAGE,CHECK_THROWS_WITH,CHECK_THROWS_WITH_AS,CHECK_MESSAGE,REQUIRE,REQUIRE_FALSE,REQUIRE_THROWS_AS,REQUIRE_THROWS_AS_MESSAGE,REQUIRE_THROWS_WITH,REQUIRE_THROWS_WITH_AS,REQUIRE_MESSAGE},
  basicstyle=\ttfamily,
  keywordstyle=\bfseries,
  stringstyle=\slshape,
  commentstyle=\slshape,
  morecomment=[s][\bfseries\slshape]{/**}{*/},
  morecomment=[l][\bfseries\slshape]{///},
  tabsize=4,
  showstringspaces=false,
  breaklines=true, breakatwhitespace=true,
  prebreak={\hbox{\quad$\rhookswarrow$}},
  postbreak={\hbox{$\lhookrightarrow$}},
  breakindent={-8pt}, breakautoindent=false,
  numbers=left, numberstyle=\tiny,
  frameshape={RYR}{N}{N}{YYY} %frame=tb,frameround=tttt
}

\lstdefinestyle{colorC++}{
  language=C++,
  morekeywords={concept,consteval,constinit,constexpr,co_await,co_return,co_yield,final,noexcept,override,requires,static_assert,thread_local,BENCHMARK,TEST_CASE,SUBCASE,SECTION,CHECK,CHECK_THROWS_AS,CHECK_THROWS_AS_MESSAGE,CHECK_MESSAGE,REQUIRE,REQUIRE_THROWS_AS,REQUIRE_THROWS_AS_MESSAGE,REQUIRE_MESSAGE},
  basicstyle=\ttfamily,
  keywordstyle=\textcolor{blue},
  stringstyle=\slshape\textcolor{red!70!black},
  commentstyle=\slshape\textcolor{green!50!black},
  morecomment=[s][\bfseries\slshape\textcolor{green!50!black}]{/**}{*/},
  morecomment=[l][\bfseries\slshape\textcolor{green!50!black}]{///},
  tabsize=4,
  showstringspaces=false,
  breaklines=true, breakatwhitespace=true,
  prebreak={\hbox{\quad\textcolor{red}{$\rhookswarrow$}}},
  postbreak={\hbox{\textcolor{red}{$\lhookrightarrow$}}},
  breakindent={-8pt}, breakautoindent=false,
  numbers=left, numberstyle=\tiny,
  frameshape={RYR}{N}{N}{YYY} %frame=tb,frameround=tttt
}

\lstdefinelanguage{CMake}{
  keywords={add_compile_definitions,add_compile_options,add_custom_command,add_custom_target,add_executable,add_library,add_link_options,add_subdirectory,add_test,cmake_minimum_required,cmake_policy,configure_file,else,enable_testing,endif,execute_process,FetchContent_Declare,FetchContent_MakeAvailable,find_package,find_library,if,include,include_directories,install,message,option,project,set,set_tests_properties,string,target_link_libraries},
  keywords=[2]{AND,BOOL,CACHE,CMAKE_BUILD_TYPE,CMAKE_CXX_FLAGS,CMAKE_CXX_STANDARD,CMAKE_CXX_STANDARD_REQUIRED,CMAKE_CXX_EXTENSIONS,CMAKE_EXPORT_COMPILE_COMMANDS,COMMAND,COMMENT,FALSE,FETCHCONTENT_QUIET,FETCHCONTENT_UPDATES_DISCONNECTED,GIT_REPOSITORY,GIT_TAG,GIT_SHALLOW,GIT_PROGRESS,INTERFACE,NAME,NOT,OBJECT,OFF,ON,OR,OUTPUT_VARIABLE,PRIVATE,PROJECT_ROOT,PROPERTIES,PUBLIC,RUN_SERIAL,STATIC,STATUS,STRING,TRUE,USES_TERMINAL_DOWNLOAD,VERSION},
  comment=[l]{\#},
  string=[s]{"}{"}
}

\lstdefinestyle{colorCMake}{
  language=CMake,
  basicstyle=\ttfamily,
  keywordstyle=\textcolor{blue},
  keywordstyle=[2]\textcolor{red!70!black},
  stringstyle=\slshape\textcolor{red!70!black},
  commentstyle=\slshape\textcolor{green!50!black},
  morecomment=[s][\bfseries\slshape\textcolor{green!50!black}]{/**}{*/},
  tabsize=4,
  showstringspaces=false,
  breaklines=true, breakatwhitespace=true,
  prebreak={\hbox{\quad\textcolor{red}{$\rhookswarrow$}}},
  postbreak={\hbox{\textcolor{red}{$\lhookrightarrow$}}},
  breakindent={-8pt}, breakautoindent=false,
  numbers=left, numberstyle=\tiny,
  frameshape={RYR}{N}{N}{YYY} %frame=tb,frameround=tttt
}

\lstdefinestyle{colorBash}{
  language=bash,
  basicstyle=\ttfamily,
  keywordstyle=\textcolor{blue},
  stringstyle=\slshape\textcolor{red!70!black},
  commentstyle=\slshape\textcolor{green!50!black},
  morecomment=[s][\bfseries\slshape\textcolor{green!50!black}]{/**}{*/},
  tabsize=4,
  showstringspaces=false,
  breaklines=true, breakatwhitespace=true,
  prebreak={\hbox{\quad\textcolor{red}{$\rhookswarrow$}}},
  postbreak={\hbox{\textcolor{red}{$\lhookrightarrow$}}},
  breakindent={-8pt}, breakautoindent=false,
  numbers=left, numberstyle=\tiny,
  frameshape={RYR}{N}{N}{YYY} %frame=tb,frameround=tttt
}

EOF
	echo '\title{'$title'}'
	echo '\author{'$author'}'
	echo '\begin{document}'
	echo '  \maketitle'

	md_files=$(find . -type f -iname "*.md")
	for f in $md_files ; do
		dirname=${f#./}
		dirname=${dirname%%/*}
		case "$dirname" in
			.idea|"cmake-build-"*|"build"|"out")
				continue
				;;
		esac
        if [ -n "$PANDOC" ]; then
            "$PANDOC" -f markdown -t pdf --variable=papersize:A4 --variable=geometry:margin=1cm "$f" > "$f.pdf"
		    echo '  \includepdf[pages=-]{'$f'.pdf}'
        else
            echo '  \verbatiminput{'$f'}'
        fi
	done

	text_files=$(find . -type f \( -iname "*.txt" \))
	for f in $text_files ; do
		filename=$(basename $f)
        case "$filename" in
            CMakeLists.txt)
                continue
                ;;
        esac
		dirname=${f#./}
		dirname=${dirname%%/*}
		case "$dirname" in
			.idea|"cmake-build-"*|"build"|"out")
				continue
				;;
		esac
		name=$(echo "$f" | sed -e 's/_/\\_/g')
		echo '  \lstinputlisting[style=colorBash,caption={'$name'}]{'$f'}'
	done

	tex_files=$(find . -type f -iname "*.tex")
	for f in $tex_files ; do
        if ! grep -qs '\\documentclass\[' "$f" ; then
		    echo '  \input{'$f'}'
        fi
	done

	python_files=$(find . -type f -iname "*.py")
	header_files=$(find . -type f \( -iname "*.h" -o -iname "*.hh" -o -iname "*.hpp" -o -iname "*.hxx" -o -iname "*.h++" \))
	source_files=$(find . -type f \( -iname "*.c" -o -iname "*.cc" -o -iname "*.cpp" -o -iname "*.cxx" -o -iname "*.c++" \))
	for f in $python_files $header_files $source_files; do
		dirname=${f#./}
		dirname=${dirname%%/*}
		case "$dirname" in
			.idea|"cmake-build-"*|"build"|"out")
				continue
				;;
		esac
		filename=$(basename $f)
		case "$filename" in
			"doctest.h")
				continue
				;;
		esac
		name=$(echo "$f" | sed -e 's/_/\\_/g')
		echo '  \lstinputlisting[style=colorC++,caption={'$name'}]{'$f'}'
	done

	cmake_files=$(find . -type f \( -iname "*.cmake" -or -name CMakeLists.txt \) )
	for f in $cmake_files ; do
		dirname=${f#./}
		dirname=${dirname%%/*}
		case "$dirname" in
			.idea|cmake-build-*|build|out)
				continue
				;;
		esac
		name=$(echo "$f" | sed -e 's/_/\\_/g')
		echo '  \lstinputlisting[style=colorCMake,caption={'$name'}]{'$f'}'
	done

    image_files=$(find . -type f \( -iname "*.eps" -o -iname "*.png" -o -iname "*.jpg" -o -iname "*.jpeg" -o -iname "*.gif" \))
	for f in $image_files ; do
		dirname=${f#./}
		dirname=${dirname%%/*}
		case "$dirname" in
			.idea|"cmake-build-"*|"build"|"out")
				continue
				;;
		esac
		name=$(echo "$f" | sed -e 's/_/\\_/g')
        echo '  \begin{figure}[!htb]'
        echo '    \centering'
		echo '    \includegraphics[width=0.65\textwidth]{'$f'}'
        echo '    \caption{'$name'}'
        echo '  \end{figure}'
	done

	echo '\end{document}'
}

echo "Generates LaTeX report from C/C++ sources and TeX files it can find in the current directory."
echo "Assumes that pdflatex (from TeX Live) and pandoc are installed."
echo -e "Usage:\n\t$0 \"Author Name\" \"Document Title\""
make_latex "$author" "$title" > listing.tex
pdflatex listing.tex && pdflatex listing.tex && okular listing.pdf
