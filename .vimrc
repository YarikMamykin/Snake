let $VIM_BUILD_FOLDER='build'
let $VIM_BIN_FOLDER='build/src'
let $VIM_BIN_NAME='Snake'
let $VIM_SRC_FOLDER='..'
let $COMPILE_COMMANDS_JSON='compile_commands.json'

function! TagIt()
  silent !clear
  silent !rm -frv tags project.files
  silent !echo "Building tags and database..."
  silent !find . -name '*.cpp' > project.files
  silent !find /usr/include/X11/ -name '*.c' -or -name '*.h' >> project.files
  silent !sed -i '/.*build.*/d' project.files
  silent !sed -i '/.*ccls.*/d' project.files
  silent !cat project.files | ctags --verbose=yes --sort=yes --c++-kinds=+p --fields=+iaS --extras=+q --language-force=C++ -f tags -L -
  silent !echo "Done"
  redraw!
endfunction

function! LinkCompileCommands()
  silent !ln -sf $(find ./${VIM_BUILD_FOLDER}/ -name "$COMPILE_COMMANDS_JSON") ./$COMPILE_COMMANDS_JSON
  redraw!
endfunction

function! Build()
  silent !clear
  silent !mkdir -p $VIM_BUILD_FOLDER
  !cd $VIM_BUILD_FOLDER && cmake $VIM_SRC_FOLDER -DCMAKE_EXPORT_COMPILE_COMMANDS=YES && make -j${CORES};
  redraw!
endfunction

function! CleanBuild()
  silent !clear
  silent !mkdir -p $VIM_BUILD_FOLDER
  !cd $VIM_BUILD_FOLDER && cmake $VIM_SRC_FOLDER -DCMAKE_EXPORT_COMPILE_COMMANDS=YES && make -j${CORES};
  redraw!
endfunction

function! Run()
  silent! !clear
  !cd $VIM_BIN_FOLDER && [ -f "$VIM_BIN_NAME" ] && ./$VIM_BIN_NAME;
  redraw!
endfunction

function! CleanBuildRun()
  silent !clear
  silent !mkdir -p $VIM_BUILD_FOLDER
  !cd $VIM_BUILD_FOLDER && cmake $VIM_SRC_FOLDER -DCMAKE_EXPORT_COMPILE_COMMANDS=YES && make -j${CORES} && cd $VIM_BIN_FOLDER && [ -f "$VIM_BIN_NAME" ] && ./$VIM_BIN_NAME;
  redraw!
endfunction

command! SetupProject call TagIt() | call SetupCcls()
command! Build call Build()
command! CleanBuild call CleanBuild()
command! CleanBuildRun call CleanBuildRun()
command! Run call Run()

nmap <Leader><F4> :CleanBuild<CR>
nmap <Leader><F5> :Run<CR>
nmap <Leader><F6> :CleanBuildRun<CR>
