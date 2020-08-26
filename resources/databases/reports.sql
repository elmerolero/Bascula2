.header on
.mode csv
.output '../reports/Corte del dia.csv'
select folio as 'FOLIO',
	numero_economico as 'NUMERO ECONOMICO',
	numero_placa as 'PLACA',
	nombre_tipo as 'TIPO DE CAJA',
	nombre_conductor as 'CONDUCTOR',
	procedencias.nombre_procedencia as 'EMPRESA',
	zona as 'ZONA',
	subzona as 'SUBZONA',
	nombre_departamento as 'DEPARTAMENTO',
	fecha as 'FECHA',
	hora_entrada as 'HORA DE ENTRADA',
	hora_salida as 'HORA DE SALIDA',
	peso_bruto as 'PESO BRUTO',
	peso_tara as 'PESO TARA',
	peso_neto as 'PESO NETO'
from tickets
join procedencias on procedencias.clave_procedencia = tickets.codigo_empresa
join departamentos on departamentos.clave_departamento = tickets.codigo_departamento
join tipos_caja on tipos_caja.clave_tipo = tipo_caja
where fecha = date( 'now', 'localtime' );