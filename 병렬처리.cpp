 out-of-order 와 uops 설명과 SIMD Vectorization of Histogram Functions
 
 같은 메모리 주소에 동시에(병렬로) write 를 하면 충돌이 발생하므로 동시에 처리하는 데이터 수 만큼의 array를 만들고 각 array 에 값을 write 하면 병렬로 처리할 수 있습니다.
  
 슈퍼스칼라 기법으로 컴파일 중 데이터의 종속성이 없다면 CPU가 알아서 병렬로 처리하는기법 이를 arr의 행으로 분리해서 동시에 unrolling 하면 병렬로 처리한다
