FROM eclipse-temurin:17-jdk

WORKDIR /app

COPY ./biblioteca-docker/*.java /app/

RUN javac *.java

CMD ["java", "TestBiblioteca"]
