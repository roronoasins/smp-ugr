---
theme : "white"
transition: "zoom"
highlightTheme: "Foundation"
logoImg: ""
slideNumber: true
---
<!-- .slide: data-background="giphy.gif" -->

# [Robot de sumo]()
# [`Spud` ]()
#### [`"Pezoncitos"` ]()

---

## Quienes somos

- Jesús Terrón
- Luis

---

## Qué hemos hecho??


<!-- 
<div class="fragment" >
- Robot de sumo basado en una estrategia defensiva
</div>
<div class="fragment" >
- Usando equipamiento electrónico suministrado por el centro exclusivamente...
</div>
<div class="fragment" >y algún trozo de cacho de madera y cartón.
</div> -->

<ul>
  <li class="fragment">Robot de sumo basado en una estrategia defensiva</li>
  <li class="fragment">Usando equipamiento electrónico suministrado exclusivamente por el centro ...</li>
  <li class="fragment">y algún trozo de cacho de madera y cartón.</li>
</ul>


---



# Objetivo:
## coste cero

Importe total 0€ (IVA incl.)



---

<img heigh="auto"  data-src="free2.png" alt="Down arrow">


---

## Código 

### (Y cosillas técnicas)

---

```c 


 * M1 -> motor derecho
 * M2 -> motor izquierdo
 * IN1 -> bumper derecho
 * IN2 -> CNY70 trasero izquierdo
 * IN3 -> CNY70 delantero derecho
 * IN4 -> CNY70 delantero izquierdo
 * IN5 -> bumper izquierdo
 * IN6 -> configurable
 * SRF02_FW -> SRF02 frontal
 * SRF02_LW -> SRF02 izquierdo
 * SRF02_RW -> SRF02 derecho


```

---

## Estados
```c
enum state {idle, 
primera_carga, 
explorar, 
maniobra, 
salir, 
sobre_linea, 
acercarse, 
empujar, //máxima potencia
empujar_der, empujar_izq}
actual = idle;
```

Muchos estados para poder separar distintos casos

---

