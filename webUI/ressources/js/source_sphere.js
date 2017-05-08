var canvas, camera, controls, scene, renderer;
var subCanvas, subCamera, subScene, subRenderer;
var sources3D = new Array(4);

init();
animate();

function init() {
    
    /*
     * Draw sources and sphere
     */
    
    // Canvas
    canvas = document.getElementById("sphere");
    
    canvas.style.height = '100%';
    canvas.style.width = '100%';
    
    // Renderer
    renderer = new THREE.WebGLRenderer( { antialias: true, canvas: canvas });
    renderer.setClearColor( 0x000000 );
    renderer.setSize(canvas.offsetWidth,canvas.offsetHeight);

    // Cameras
    camera = new THREE.PerspectiveCamera( 70, canvas.offsetWidth/canvas.offsetHeight , 1, 4 );
    camera.position.z = 2.1;

    // Cameras controls
    controls = new THREE.TrackballControls( camera,canvas );
    controls.rotateSpeed = 5.0;
    controls.noZoom = true;
    controls.noPan = true;
    controls.dynamicDampingFactor = 0.2;

    // Scene
    scene = new THREE.Scene();

    // Sphere
    var sphereGeometry = new THREE.SphereGeometry( 1, 10, 10);
    var sphereMaterial = new THREE.MeshBasicMaterial( {color: 0xffffff, wireframe:true} ); 
    
    var sphere = new THREE.Mesh( sphereGeometry, sphereMaterial );
    scene.add(sphere);
    
    // Sources
    var sourceGroup = new THREE.Group();

    var sourceGeometry = new THREE.SphereGeometry( 0.08, 10, 10);

    var colors = ["rgb(75,192,192)","rgb(192,75,192)","rgb(192,192,30)","rgb(0,200,40)"]
    
    for(var i = 0; i<4; i++) {
        
        var sourceMaterial = new THREE.MeshBasicMaterial( {color: colors[i], wireframe:false} );
        var source = new THREE.Mesh( sourceGeometry, sourceMaterial );
        source.visible = false;
        
        sources3D[i] = source;
        sourceGroup.add(sources3D[i]);
    }

    scene.add( sourceGroup );
    
    /*
     * Draw sub canvas with axis
     */
    
    // Canvas
    subCanvas = document.getElementById("axis");
    
    // Renderer
    subRenderer = new THREE.WebGLRenderer( { antialias: true, canvas: subCanvas });
    subRenderer.setClearColor(0x000000);
    subRenderer.setSize(80,80);
    
    // Scene
    subScene = new THREE.Scene();
    
    // Camera
    subCamera = new THREE.PerspectiveCamera(70,1,0.1,5);
    subCamera.position.z = 3.5;
    subCamera.up = camera.up;
    
    // Axis
    var axis = new THREE.AxisHelper(1.2);
    console.log(axis);
    subScene.add( axis );
    
    // Add axes labels
    var loader = new THREE.FontLoader();
    loader.load( 'fonts/helvetiker_regular.typeface.json', function ( helFont ) {
        
        var  textGeo = new THREE.TextGeometry('X', {
             size: 0.3,
             height: 0.001,
             curveSegments: 6,
             font: helFont,
             style: "normal"       
        });

        var  textMaterial = new THREE.MeshBasicMaterial({ color: "rgb(255,0,0)" });
        var  text = new THREE.Mesh(textGeo , textMaterial);

        text.position.x = 0.9;
        text.position.y = 0.01;
        text.position.z = 0;
        text.rotation = 0;
        subScene.add(text);
        
        var  textGeo = new THREE.TextGeometry('Y', {
             size: 0.3,
             height: 0.001,
             curveSegments: 6,
             font: helFont,
             style: "normal"       
        });

        var  textMaterial = new THREE.MeshBasicMaterial({ color: "rgb(0,255,0)" });
        var  text = new THREE.Mesh(textGeo , textMaterial);

        text.position.x = 0.03;
        text.position.y = 0.9;
        text.position.z = 0;
        text.rotation = 0;
        subScene.add(text);
        
        var  textGeo = new THREE.TextGeometry('Z', {
             size: 0.1,
             height: 0.001,
             curveSegments: 6,
             font: helFont,
             style: "normal"       
        });

        var  textMaterial = new THREE.MeshBasicMaterial({ color: "rgb(0,0,255)" });
        var  text = new THREE.Mesh(textGeo , textMaterial);

        text.position.x = 0.01;
        text.position.y = 0.01;
        text.position.z = 1.2;
        text.rotation = 0;
        subScene.add(text);
        
    } );

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
    
    controls.update();
    
    subCamera.rotation.copy(camera.rotation);
    subCamera.position.copy(camera.position);
    
    render();
}

function render() {
    
    renderer.render( scene, camera );
    subRenderer.render( subScene, subCamera);
    
}

document.addEventListener('data', function(e) {
    
    currentFrame.sources.forEach(function(source,index) {
        
        sources3D[index].visible = source.active && source.selected;
        
        sources3D[index].position.x = Math.cos(source.long)*Math.sin(source.lat);
        sources3D[index].position.y = Math.sin(source.long)*Math.sin(source.lat)
        sources3D[index].position.z = Math.cos(source.lat);
        
    });
    
},false);