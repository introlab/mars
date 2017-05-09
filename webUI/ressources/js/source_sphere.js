var canvas, camera, controls, scene, renderer;
var subCanvas, subCamera, subScene, subRenderer;
var labelX, labelY, labelZ;
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
    camera.position.y = -2.1;
    camera.up.set(0,0,1);

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
    subCamera = new THREE.PerspectiveCamera(90,1,0.1,5);
    subCamera.position.z = 3.5;
    subCamera.up = camera.up;
    
    // Axis
    var axis = new THREE.AxisHelper(1.2);
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
        labelX = new THREE.Mesh(textGeo , textMaterial);

        labelX.position.x = 1.2;
        labelX.position.y = 0.01;
        labelX.position.z = 0;
        subScene.add(labelX);
        
        var  textGeo = new THREE.TextGeometry('Y', {
             size: 0.3,
             height: 0.001,
             curveSegments: 6,
             font: helFont,
             style: "normal"       
        });

        var  textMaterial = new THREE.MeshBasicMaterial({ color: "rgb(0,255,0)" });
        labelY = new THREE.Mesh(textGeo , textMaterial);

        labelY.position.x = 0.03;
        labelY.position.y = 1.2;
        labelY.position.z = 0;
        subScene.add(labelY);
        
        var  textGeo = new THREE.TextGeometry('Z', {
             size: 0.3,
             height: 0.001,
             curveSegments: 6,
             font: helFont,
             style: "normal"       
        });

        var  textMaterial = new THREE.MeshBasicMaterial({ color: "rgb(0,0,255)" });
        labelZ = new THREE.Mesh(textGeo , textMaterial);

        labelZ.position.x = 0.01;
        labelZ.position.y = 0.01;
        labelZ.position.z = 1.2;
        subScene.add(labelZ);
        
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
    
    try {
        subCamera.rotation.copy(camera.rotation);
        subCamera.position.copy(camera.position);

        labelX.rotation.copy(camera.rotation);
        labelY.rotation.copy(camera.rotation);
        labelZ.rotation.copy(camera.rotation);
    }
    
    catch(err) {
        // Scene not loaded
    }
    
    finally {
        render();
    }
}

function render() {
    
    renderer.render( scene, camera );
    subRenderer.render( subScene, subCamera);
    
}

document.addEventListener('data', function(e) {
    
    currentFrame.sources.forEach(function(source,index) {
        
        sources3D[index].visible = source.active && source.selected && !(source.x == 0 && source.y == 0 && source.z == 0);
        
        sources3D[index].position.x = source.x;
        sources3D[index].position.y = source.y;
        sources3D[index].position.z = source.z;
        
    });
});

document.addEventListener('update-selection',function(e){
    
    currentFrame.sources.forEach(function(source,index) {
        sources3D[index].visible = source.active && source.selected;
    });  
});