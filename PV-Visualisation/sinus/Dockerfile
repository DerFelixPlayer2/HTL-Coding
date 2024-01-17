FROM node:18.12.0-alpine3.15

WORKDIR /app

COPY package.json package.json
COPY package-lock.json package-lock.json
RUN npm install

COPY sinus.js sinus.js

ENTRYPOINT [ "npm", "run", "sinus" ]
