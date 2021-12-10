filetype plugin indent on
set nu rnu
set ai ts=4 shiftwidth=4 sts=4 et
set spr sb
set clipboard=unnamed,unnamedplus
set noswapfile nobk
set undofile
set undodir=~/.vim/undodir
vmap < <gv
vmap > >gv
nmap \cp :let @+=expand("%:p")<CR>
