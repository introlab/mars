var container, stats, canvas, area;
var camera, controls, scene, renderer;
var objects = [];
init();
animate();

function init() {
    
    canvas = document.getElementById("sphere");
    area = document.getElementById("draw-zone");
    
    canvas.style.height = '100%';
    canvas.style.width = '100%';
    
    console.log(canvas);
    console.log(canvas.offsetWidth);
    console.log(canvas.offsetHeight);

    camera = new THREE.PerspectiveCamera( 70, canvas.offsetWidth/canvas.offsetHeight , 1, 4 );
    camera.position.z = 2.1;

    controls = new THREE.TrackballControls( camera,canvas );
    controls.rotateSpeed = 5.0;
    controls.noZoom = true;
    controls.noPan = true;
    controls.dynamicDampingFactor = 0.2;

    scene = new THREE.Scene();

    var sphereGeometry = new THREE.SphereGeometry( 1, 10, 10);
    var sphereMaterial = new THREE.MeshBasicMaterial( {color: 0xffffff, wireframe:true} );
    var sphere = new THREE.Mesh( sphereGeometry, sphereMaterial ); 

    var sourceGeometry = new THREE.SphereGeometry( 0.08, 10, 10);
    var sourceMaterial = new THREE.MeshBasicMaterial( {color: 0x00ffff, wireframe:false} );
    var source = new THREE.Mesh( sourceGeometry, sourceMaterial );

    source.position.x = 1;

    var sourceGroup = new THREE.Group();

    sourceGroup.add(sphere);
    sourceGroup.add(source);

    scene.add( sourceGroup );

    renderer = new THREE.WebGLRenderer( { antialias: true, canvas: canvas });
    renderer.setClearColor( 0x000000 );
    renderer.setPixelRatio( window.devicePixelRatio );
    renderer.setSize(canvas.offsetWidth,canvas.offsetHeight);
    renderer.sortObjects = false;
    renderer.shadowMap.enabled = false;
    
    stats = new Stats();
    
    //area.appendChild( stats.dom );

    window.addEventListener( 'resize', onWindowResize, false );
}

function onWindowResize() {
    camera.aspect = canvas.offsetWidth/canvas.offsetHeight ;
    camera.updateProjectionMatrix();
    renderer.setSize(canvas.offsetWidth,canvas.offsetHeight);
    
    canvas.style.height = '100%';
    canvas.style.width = '100%';
}

function animate() {
    requestAnimationFrame( animate );
    render();
    stats.update();
}

function render() {
    controls.update();
    renderer.render( scene, camera );
}