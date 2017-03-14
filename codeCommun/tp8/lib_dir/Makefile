########               Makefile de la librairie in-house               ########
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
SRC=moteurA.cpp moteurB.cpp can.cpp timer16.cpp del.cpp

# Nom de la librairie
PROJECTNAME=libinf1995

# Acces au dossier include contenant les fichiers .h
INC=-I ../include

# Flags pour compilateur d'archive AVR
AFLAGS=crs

# Compilateur d'archive AVR
AR=avr-ar

# Cible de compilation
TRG=$(PROJECTNAME).a

# Commande specifique pour creer la librairie
TRG_CMD=$(AR) $(AFLAGS) $(TRG) $(OBJDEPS)

# Appel au makefile commun
-include ../Makefile.common
