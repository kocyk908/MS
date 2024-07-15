1. git clone
2. git branch <nowy_branch>
3. git checkout <nowy_branch>
4. robota 
5. git add
6. git commit
7. git checkou <main/master>
8. git pull origin main/master
9. git merge <new_branch>
10. git push origin main/master 


Update 11.07.24

Echo problematyczne gdy argument podany jest w "", jeszcze nie ogarnąłem tego

Update 07.07.24

Udało mi sie już jakoś połączyć procesy w pętlach. 
Póki co to działałem na harkodowanych zmiennych jak path, ilość komend itp
Na tą chwilę potrzeba:

1. Uzupełnić int num_of_cmds w s_gen - długość listy komend. Ja to mogę zrobić.		# w trakcie
2. Uzupełnić char *path w s_command - ścieżka do programu np: "/usr/bin/cat"		
3. Uzupełnić redirsy:
    a) int input_redir - będzie zawirać file descriptor będący wynikiem funckji open
    b) analogicznie output_redir;

Uzupełnienie tego powinno już pozwolić połączyć to wszystko.
Potem zajmiemy sie heredoc i append.

--------------------------------------------------------------------------

Robię tak że execute_pipeline przyjmie następujące informacje
1. input redirection w formie ścieżki pliku w postaci 
    stringa np: "infile.txt"
2. porzebuję ścieżki do każdej komendy znajdującej się command.
    Utworzyłem membere commant->path. Scieżka powinna wyglądać np:
    "/usr/bin/ls" dla programu ls 
