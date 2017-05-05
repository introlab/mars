var container, stats, canvas, area, axis;
var camera, controls, scene, renderer;
var objects = [];
var sources3D = new Array(4);
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
    
    var sourceGroup = new THREE.Group();
    sourceGroup.add(sphere);

    var sourceGeometry = new THREE.SphereGeometry( 0.08, 10, 10);
    
    var colors = ["rgb(75,192,192)","rgb(192,75,192)","rgb(192,192,30)","rgb(0,200,40)"]
    
    for(var i = 0; i<4; i++) {
        
        console.log('Sourcing...');
        var sourceMaterial = new THREE.MeshBasicMaterial( {color: colors[i], wireframe:false} );
        var source = new THREE.Mesh( sourceGeometry, sourceMaterial );
        source.visible = false;
        
        sources3D[i] = source;
        sourceGroup.add(sources3D[i]);
    }

    scene.add( sourceGroup );
    
    axis = new THREE.AxisHelper(1.2);
    scene.add( axis );
    
    var loader = new THREE.FontLoader();
    loader.load( 'fonts/helvetiker_regular.typeface.json', function ( helFont ) {
        
        var  textGeo = new THREE.TextGeometry('X', {
             size: 0.1,
             height: 0.001,
             curveSegments: 6,
             font: helFont,
             style: "normal"       
        });

        var  textMaterial = new THREE.MeshBasicMaterial({ color: "rgb(255,0,0)" });
        var  text = new THREE.Mesh(textGeo , textMaterial);

        text.position.x = 1.1;
        text.position.y = 0.01;
        text.position.z = 0;
        text.rotation = 0;
        scene.add(text);
        
        var  textGeo = new THREE.TextGeometry('Y', {
             size: 0.1,
             height: 0.001,
             curveSegments: 6,
             font: helFont,
             style: "normal"       
        });

        var  textMaterial = new THREE.MeshBasicMaterial({ color: "rgb(0,255,0)" });
        var  text = new THREE.Mesh(textGeo , textMaterial);

        text.position.x = 0.01;
        text.position.y = 1.1;
        text.position.z = 0;
        text.rotation = 0;
        scene.add(text);
        
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
        scene.add(text);
        
    } );

    renderer = new THREE.WebGLRenderer( { antialias: true, canvas: canvas });
    renderer.setClearColor( 0x000000 );
    renderer.setPixelRatio( window.devicePixelRatio );
    renderer.setSize(canvas.offsetWidth,canvas.offsetHeight);
    renderer.sortObjects = false;
    renderer.shadowMap.enabled = false;

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
}

function render() {
    controls.update();
    renderer.render( scene, camera );
}

document.addEventListener('data', function(e) {
    
    currentFrame.sources.forEach(function(source,index) {
        
        sources3D[index].visible = source.active && source.selected;
        
        sources3D[index].position.x = Math.cos(source.long)*Math.sin(source.lat);
        sources3D[index].position.y = Math.sin(source.long)*Math.sin(source.lat)
        sources3D[index].position.z = Math.cos(source.lat);
        
    });
    
},false);