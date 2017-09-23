//Experimenting with different styles of Javascript coding

//Java Style Javascript
//Create an IIFE which returns the main function which is then
//invoked with optional args.
(function() {

    let name = "";    
   
    function main(args) {
        name = args || "Nameless";
        console.log("This is a Java style program.");        
        greet();
    }

    function greet() {
        console.log("Hello, " + name + "!");        
    }

    return main;
})()("Tyler");

//C Style Javascript
// everything just starts with main()...
main();

function main() {
    let name = "Tyler";

    console.log("This is a C-style program.");
    greet(name);
}

function greet(name) {
    console.log("Hello, " + name + "!");
}

