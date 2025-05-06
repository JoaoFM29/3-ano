
aluno(1,joao,m).
aluno(2,antonio,m).
aluno(3,carlos,m).
aluno(4,luisa,f).
aluno(5,maria,f).
aluno(6,isabel,f).

curso(1,lei).
curso(2,miei).
curso(3,lcc).

%disciplina(cod,sigla,ano,curso)
disciplina(1,ed,2,1).
disciplina(2,ia,3,1).
disciplina(3,fp,1,2).

%inscrito(aluno,disciplina)
inscrito(1,1).
inscrito(1,2).
inscrito(5,3).
inscrito(5,5).
inscrito(2,5).

%nota(aluno,disciplina,nota)
nota(1,1,15).
nota(1,2,16).
nota(1,5,20).
nota(2,5,10).
nota(3,5,8).

%copia(alunoQCopia,alunoCopiado)
copia(1,2).
copia(2,3).
copia(3,4).

% --alinea i)
naoinscrito(NOME) :- aluno(N, NOME, _), not(inscrito(N,_)).
naoinscritos(L) :- findall(A,naoinscrito(A), L).

concatenar([], L2, L2).
concatenar([X|R], L2, [X|L]):- concatenar(R,L2,l).

% --alinea i1)
discNI(A):- aluno(NUMERO, A, _),
            inscrito(NUMERO, D),
            not(disciplina(D,_,_,_)).

naoinscrito2(S) :- findall(Aluno, disciplinaNI(Aluno), L),
                    naoinscrito(R),
                    concatenar(L,R,S).

% --alinea iii)
somaL([],0).
somaL([H|T], R) :- somaL(T, R1), R is R1+H.

tamL([_], 1) :- !.
tamL([_|L], T) :- tamL(L,X), T is X+1.

mediaA([],0).
mediaA(L,M) :- somaL(L,S), tamL(L,T),  M is S / T.

media(Aluno,M):- aluno(Numero,Aluno,_),
                 findall(N,nota(Numero,_,N), Ls),
                 mediaA(Ls,M).

% --alinea iv)
lista_acima_media(M,R):- findall(Aluno, (media(Aluno,MediaA), MediaA>M), R).
acimaDaMedia(Aluno) :- findall(N, nota(_,_,N), L), mediaA(L,M), lista_acima_media(M,Aluno).

%--alinea v)
copiaram(Nome):- aluno(N,Nome,_), copia(_,N).
tqCopiaram(L):- findall(Nome,copiaram(Nome), L).

%--alinea vi)
copiouDirInD(X,N):- copia(X,Y).
copiouDirInD(X,Y):- copia(A,Y), copiouDirInD(X,A).

%--alinea vii)
maptoList([],[]).
maptoList([H|T], [N|T1]):- aluno(H,N,_), maptoList(T,T1); maptoList(T,T1).
