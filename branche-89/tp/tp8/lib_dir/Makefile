#############################################
###  Makefile de la librairie écrit par:  ###
###           Guillaume Renaud            ###
###         Loic Bellmare-Alford          ###
###           Julien Bergeron             ###
###         Yann-Joel D. Tessier          ###
###                                       ###
###           Équipe 08-89                ###
###          INF1995 - 2017               ###
#############################################

#Les fichiers contenant les fonctionnalités
CPP=pwm.cpp

#Le nom de la librairie
PROJECTNAME=lib89

#L'acces au dossier include contenant les fichiers .h
INC=-I ../include

#Ligne de commande pour la creation de l'archive
AR=avr-ar crs

#La cible
TRG=$(PROJECTNAME).a

#La commande specifique pour creer la librairie
TRG_CMD=$(AR) $(TRG) $(OBJDEPS)

#
C=-c

#L
-include ../Makefile.common
