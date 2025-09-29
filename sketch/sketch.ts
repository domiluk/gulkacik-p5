let bt: number
let koniec: number
let mode: number

let main_menu: p5.Image, main_xko: p5.Image, main_aut: p5.Image
let main_hra: p5.Image, main_nast: p5.Image
let sipka: p5.Image
let autori: p5.Image

function preload() {
    main_menu = loadImage("images/main_menu.bmp")
    main_xko = loadImage("images/xko.bmp")
    main_aut = loadImage("images/menudlx_aut.bmp")
    main_hra = loadImage("images/menudlx_hra.bmp")
    main_nast = loadImage("images/menudlx_nast.bmp")
    autori = loadImage("images/autori.bmp")
    sipka = loadImage("images/sipka.bmp")
}

function setup() {
    createCanvas(800, 600)

    bt = 0

    koniec = 0
    mode = 0
}

function draw() {
    // main menu
    if (mode == 0) {
        image(main_menu, 0, 0)

        //xko
        if (mir(670, 0, 670 + main_xko.width, main_xko.height)) {
            image(main_xko, 670, 0)
            if (mouseIsPressed && mouseButton === LEFT) {
                mode = -1
            }
        }

        //hra 90/150
        if (mir(90, 150, 90 + main_hra.width, 150 + main_hra.height)) {
            image(main_hra, 90, 150)
            if (mouseIsPressed && mouseButton === LEFT) {
                mode = 1
                //rest(120)
            }
        }

        //nastavenia 90/240
        if (mir(90, 240, 90 + main_nast.width, 240 + main_nast.height)) {
            image(main_nast, 90, 240)

            if (mouseIsPressed && mouseButton === LEFT) {
                mode = 2
            }
        }

        //autori 90/325
        if (mir(90, 325, 90 + main_aut.width, 325 + main_aut.height)) {
            image(main_aut, 90, 325)
            if (mouseIsPressed && mouseButton === LEFT) {
                // TODO: apeg_play_mpg("m2a.ogg", screen, 0, NULL)
                mode = 3
            }
        }
    }

    // autori
    if (mode == 3) {
        image(autori, 0, 0)

        if (mir(660, 0, 670 + sipka.width, sipka.height)) {
            image(sipka, 660, 0)
            if (mouseIsPressed && mouseButton === LEFT) {
                mode = 0
                // rest(300)
            }
        }
    }
}

function mir(x1: number, y1: number, x2: number, y2: number) {
    return mouseX >= x1 && mouseX < x2 && mouseY >= y1 && mouseY < y2
}
