import QtQuick 2.2

/* Ce fichier dessinera et gèrera les cases occupées dans le jeu */
/* Il est en partie généré automatiquement */

Rectangle {
    id: LesCases
    property string value: ""
    width: 60
    height: 60
    color: "green"
    radius: 5

    Text {
        id: valeur
        /* Value sera le chiffre de la case */
        text: value
        font.pointSize: 25
        anchors.centerIn: parent
        color: "black"
    }

/* Changer l'état des cases en fontion de ses caractéristiques */

states:[
    /* name : quel numéro */
    /* target, quel rectangle changer */

    State{ name:"0"
        PropertyChanges{target: LesCases; color: "white"}
    },
    State{ name:"2"
        PropertyChanges{target: LesCases; color: "yellow"}
    },
    State{ name:"4"
        PropertyChanges{target: LesCases; color: "orange"}
    },
    State{ name:"8"
        PropertyChanges{target: LesCases; color: "purple"}
    },
    State{ name:"16"
        PropertyChanges{target: LesCases; color: "red"}
    },
    State{ name:"32"
        PropertyChanges{target: LesCases; color: "gray"}
    },
    State{ name:"64"
        PropertyChanges{target: LesCases; color: "gray"}
    },
    State{ name:"128"
        PropertyChanges{target : LesCases; color: "gray";}
        },
    State{ name:"256"
        PropertyChanges{target : LesCases; color: "gray";}
        },
    State{ ame:"512"
        PropertyChanges{target : LesCases; color: "gray";}
        },
    State{ name:"1024"
        PropertyChanges{target : LesCases; color: "gray";}
        },
    State{ name:"2048"
        PropertyChanges{target : LesCases; color: "gray";}
        }
    ]
}