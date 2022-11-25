const express = require('express')
const { MongoClient, ObjectId } = require('mongodb')

// const url = "mongodb://127.0.0.1:27017";
const url =
  'mongodb+srv://admin:HQX1ahYOCTJKJM19@cluster0.qzen5vh.mongodb.net/?retryWrites=true&w=majority'
const bancoDadosNome = 'API_CONSUMO'

async function main() {
  console.log('Conectando ao banco de dados...')

  // Realiza a conexão com o client
  const client = await MongoClient.connect(url)

  // Obtém acesso ao banco de dados
  const bancoDados = client.db(bancoDadosNome)

  // Obtém acesso à collection
  const collection = bancoDados.collection('Sensores')
  console.log('Banco de dados conectado com sucesso!')
  const app = express()

  // Sinalizamos que estamos usando JSON no Body
  app.use(express.json())

  // Endpoint [GET] /sensor - READ ALL (Ler todo os sensores de temperatura)
  app.get('/sensor', async function (req, res) {
    // Leio todos os documentos da collection
    const item = req.body
    if (item.tipo == 'T') {
      const documentos = await collection.find({ tipo: item.tipo }).toArray()
      // Envio como resposta para o endpoint
      res.send(documentos)
    } else {
      const documentos = await collection.find({ tipo: item.tipo }).toArray()
      // Envio como resposta para o endpoint
      res.send(documentos)
    }
  })

  // Endpoint [GET] /sensor/:id - READ BY ID (Ler um determinado sensor de temperatura)
  app.get('/sensor/:id', async function (req, res) {
    // Pegamos o parâmetro de rota ID
    const id = req.params.id
    const tipo = req.body.tipo

    // Realizamos uma busca no banco de dados
    const item = await collection.findOne({
      _id: parseInt(id),
      tipo: req.body.tipo
    })

    if (item) res.send(item)
    else res.status(500).send('Sensor nao encontrado')

    // Exibimos o item encontrado
  })

  // Endpoint [GET] /itens/:id - READ BY ID (pega dados de sensor de consumo)
  app.get('/sensor_consumo', async function (req, res) {
    // Pegamos o parâmetro de rota ID
    const id = req.params.id

    // Realizamos uma busca no banco de dados
    const item = await collection.findOne({
      _id: parseInt(id)
    })

    if (item) res.send(item)
    else res.send('id nao encontrado')

    // Exibimos o item encontrado
  })

  // Endpoint [PUT] /sensor_update/:id - UPDATE BY ID (Atualizar nome pelo id)
  app.put('/sensor_update/:id', async function (req, res) {
    // Pegamos o parâmetro de rota ID
    const id = req.params.id
    // Pegamos o objeto enviado no body
    const verifica_id = await collection.findOne({
      _id: parseInt(id),
      tipo: req.body.tipo
    })
    const item = req.body
    if (verifica_id) {
      // Atualizamos o item no banco de dados
      await collection.updateOne(
        { _id: parseInt(id) },
        { $set: { nome: item.nome } }
      )
      res.send('Item atualizado com sucesso!')
    } else res.status(500).send('ID nao encontrado')
  })

  // Endpoint [PUT] /itens/:id - UPDATE BY ID (Atualizar pelo ID)
  app.put('/sensor_update_disposicao/:id', async function (req, res) {
    // Pegamos o parâmetro de rota ID
    const id = req.params.id
    const verifica_id = await collection.findOne({
      _id: parseInt(id),
      tipo: req.body.tipo
    })
    // Pegamos o objeto enviado no body
    const item = req.body
    if (verifica_id) {
      if (item.disposicao == true) {
        await collection.updateOne(
          { _id: parseInt(id) },
          { $set: { diposicao: true } }
        )
      } else {
        await collection.updateOne(
          { _id: parseInt(id) },
          { $set: { diposicao: false } }
        )
      }
      res.send('Disposicao atualizada com sucesso!')
    } else res.status(500).send('ID nao encontrado')
  })

  app.listen(process.env.PORT || 3000, function () {
    console.log('http://127.0.0.1:3000')
  })
}

main()
