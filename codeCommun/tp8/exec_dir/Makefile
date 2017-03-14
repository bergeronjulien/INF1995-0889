########                   Makefile de l'executable                    ########
#####                                                                     #####
#####                    Makefile produit et ecrit par                    #####
#####                          Guillaume Renaud                           #####
#####                        Loic Bellmare-Alford                         #####
#####                           Julien Bergeron                           #####
#####                        Yann-Joel D. Tessier                         #####
#####                                                                     #####
#####                            Equipe 08-89                             #####
#####                           INF1995 - H2017                           #####
#####                                                                     #####
#####                 Makefile inspire de Maxime Perusse                  #####
#####                  https://github.com/maperr/inf1995                  #####
#####                                                                     #####
###############################################################################

################### Definition des variables du make local ####################

# Fichiers sources
SRC=tp8.cpp

# Nom du robot (executable)
PROJECTNAME=optimusprime

# Acces a la librairie in-house
LIBS=-L ../lib_dir -linf1995

# Cible de compilation
TRG=$(PROJECTNAME).out

# Commande specifique pour creer l'executable
TRG_CMD=$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) \
	-lm $(LIBS)

# Reference aux includes de la librairie in-house
INCL=$(INC)

# Appel au makefile commun
-include ../Makefile.common