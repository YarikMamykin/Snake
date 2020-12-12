let $VIM_BUILD_FOLDER='build'
let $VIM_SRC_FOLDER='..'
let $VIM_BIN_NAME='Snake'
let $VIM_BIN_FOLDER='build/src'
let $VIM_COMPILE_COMMAND="cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=YES"
let $VIM_BUILD_COMMAND='make'
let $VIM_INSTALL_COMMAND='true'
let $COMPILE_COMMANDS_JSON='compile_commands.json'
let $VIM_TESTS_BIN_NAME='runUnitTests'
let $VIM_TESTS_BIN_FOLDER='build/test'

function! TagIt()
  silent !rm -frv tags 
  silent !echo "Building tags..."

  silent !find . -name '*.c' -o -name "*.cc" -o -name '*.cpp' -o -name '*.h' -o -name '*.hpp' > project.files
  silent !cat project.files | ctags --verbose=yes --sort=yes --c++-kinds=+p --fields=+iaS --extras=+q --language-force=C++ -f tags -L -

  silent !find /usr/include/X11/ -name '*.c' -o -name "*.cc" -o -name '*.cpp' -o -name '*.h' -o -name '*.hpp' > x11.files
  silent !cat x11.files | ctags --verbose=yes --sort=yes --c++-kinds=+p --fields=+iaS --extras=+q --language-force=C++ -f x11tags -L -
  set tags+=./x11tags

  silent !echo "Done"
  redraw!
endfunction

function! Clean()
  silent !clear
  !rm -frv $VIM_BUILD_FOLDER/**
  redraw!
endfunction

function! Build()
  !mkdir -p $VIM_BUILD_FOLDER && cd $VIM_BUILD_FOLDER && rm -frv * && $VIM_COMPILE_COMMAND $VIM_SRC_FOLDER && $VIM_BUILD_COMMAND -j$CORES && $VIM_INSTALL_COMMAND
  redraw!
endfunction

function! BuildQuick()
  !cd $VIM_BUILD_FOLDER && $VIM_BUILD_COMMAND -j$CORES && $VIM_INSTALL_COMMAND
  redraw!
endfunction

function! LinkCompileCommands()
  !mkdir -p $VIM_BUILD_FOLDER && cd $VIM_BUILD_FOLDER && rm -frv * && $VIM_COMPILE_COMMAND $VIM_SRC_FOLDER && cd - && rm -frv $COMPILE_COMMANDS_JSON && ln -sf $(find . -name "$COMPILE_COMMANDS_JSON") ./$COMPILE_COMMANDS_JSON
  redraw!
endfunction

function! Run()
  !cd $VIM_BIN_FOLDER && if [ -f "$VIM_BIN_NAME" ]; then ./$VIM_BIN_NAME; fi
  redraw!
endfunction

function! RunTests()
  !cd $VIM_TESTS_BIN_FOLDER && if [ -f "$VIM_TESTS_BIN_NAME" ]; then ./$VIM_TESTS_BIN_NAME; fi
  redraw!
endfunction

function! Debug()
  !cd $VIM_BIN_FOLDER && if [ -f "$VIM_BIN_NAME" ]; then gdb ./$VIM_BIN_NAME; fi
  redraw!
endfunction

nmap <F4> :call TagIt()<CR>:call LinkCompileCommands()<CR>
nmap <Leader><F4> :call Build()<CR>
nmap <Leader><F5> :call Run()<CR>
nmap <Leader><F6> :call Debug()<CR>
nmap <Leader><F7> :call RunTests()<CR>
nmap <Leader><F8> :call BuildQuick()<CR>

function! Switch()
  let filename = expand("%:t:r")
  let fileext = expand("%:e")
  if (fileext == "cpp")
    find %:t:r.hpp
  endif
  if (fileext == "hpp")
    find %:t:r.cpp
  endif
endfunction

set wildignore+=*/build/*
